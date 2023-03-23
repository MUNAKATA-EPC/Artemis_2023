#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#define BUTTON_PIN 10  // use pin 2 on Arduino Uno & most boards

MPU6050 mpu = MPU6050(0x69);

bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

float ypr[3], raw_ypr[3], offset_ypr[3];           //yaw   yaw/pitch/roll container and gravity vector

int DegData;

typedef struct{
  int index = 0;
  int value = 0;
} IR_SENSOR;

IR_SENSOR IR_Sen[16];

int theta;
int radius;

void CulcDegData() {
  if (!dmpReady) return;
  if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {// Get the Latest packet
    Quaternion _quaternion;
    VectorFloat _gravity;
    mpu.dmpGetQuaternion(&_quaternion, fifoBuffer);
    mpu.dmpGetGravity(&_gravity, &_quaternion);
    mpu.dmpGetYawPitchRoll(raw_ypr, &_quaternion, &_gravity);
  }
  
  ypr[0] = raw_ypr[0] - offset_ypr[0];
  
  DegData = ypr[0] * 180/M_PI / 2;
  if(DegData < 0)
    DegData = DegData + 180;
}

void AttachOffset(){
  offset_ypr[0] = raw_ypr[0];
}

//比較対象のvalue値の比較を行います。
//n1<n2 : 1 
//n1>n2 : -1
//n1=n2 : 0
int CompareIRValue(const void* n1, const void* n2){
  if(((IR_SENSOR*)n1)->value < ((IR_SENSOR*)n2)->value)
    return -1;
  else if(((IR_SENSOR*)n1)->value > ((IR_SENSOR*)n2)->value)
    return 1;
  else 
    return 0;
}

bool CheckAllSensor(){
  bool ret = false;
  for(int i = 0; i < 16; i++)
  {
    if(IR_Sen[i].value <= 920)
    {
      ret = true;
    }
  }
  return ret;
}

void setup() {
  
  for(int i = 0; i < 16; i++)
  {
    pinMode(i, INPUT);
  }

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
      Wire.begin();
      Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
      Fastwire::setup(400, true);
  #endif
  
  Serial1.begin(115200);
  Serial2.begin(115200);

  mpu.initialize();
  mpu.dmpInitialize();

  mpu.setZGyroOffset(47); //64
  mpu.setZAccelOffset(560); //724

  if (devStatus == 0) {
    mpu.CalibrateAccel(6);
    mpu.CalibrateGyro(6);
    mpu.PrintActiveOffsets();
   
    mpu.setDMPEnabled(true);
    mpuIntStatus = mpu.getIntStatus();

    dmpReady = true;

    packetSize = mpu.dmpGetFIFOPacketSize();
  }
}

void loop() {
  //if(digitalRead(BUTTON_PIN) == LOW)
  //  AttachOffset();
  
  CulcDegData();
  
  for(int i = 0; i < 16; i++)
  {
    IR_Sen[i].value = analogRead(i);
    IR_Sen[i].index = i + 1;
  }
  
  qsort(IR_Sen, sizeof(IR_Sen) / sizeof(IR_Sen[0]), sizeof(IR_SENSOR), CompareIRValue);
  
  if(CheckAllSensor() == true)
  {
    if(IR_Sen[0].index == 16 && IR_Sen[1].index == 1)  //IRの場所が1番目の場合{
      theta = 32;
    else if(IR_Sen[0].index == 1 && IR_Sen[1].index == 16)  //IRの場所が1番目の場合
      theta = 1;
    else if(IR_Sen[0].index > IR_Sen[1].index) //一番反応しているIRの場所が二番目より右側の場合
      theta = IR_Sen[0].index * 2 - 1;
    else if(IR_Sen[0].index < IR_Sen[1].index) //一番反応しているIRの場所が二番目より左側の場合
      theta = IR_Sen[0].index * 2;

    theta = theta / 32.0 * 180;

    radius = (IR_Sen[0].value + IR_Sen[1].value) / 2 / 1023.0 * 180.0; 

  }
  else
  {
    theta = 255;
    radius = 255;
  }

  Serial1.write(DegData);
  Serial1.flush();
  
  Serial2.write(255);
  Serial2.write(theta);
  Serial2.write(radius);
  Serial2.flush();
}
