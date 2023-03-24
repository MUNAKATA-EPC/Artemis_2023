//[-1545,-1544] --> [-27,9]	[577,577] --> [-31,390]	[1049,1050] --> [16361,16389]	[-106,-105] --> [0,1]	[85,86] --> [0,1]	[11,12] --> [0,1]

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

MPU6050 mpu;

#define OUTPUT_READABLE_YAWPITCHROLL

#define BUTTON_PIN 10  // use pin 2 on Arduino Uno & most boards

bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

float ypr[3], raw_ypr[3], offset_ypr[3];           //yaw   yaw/pitch/roll container and gravity vector

int DegData;

void CulcDegData();
void AttachOffset();

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
  
  DegData = ypr[0] * 180/M_PI/2;
  if(DegData < 0)
    DegData = DegData + 180;
}

void AttachOffset(){
  offset_ypr[0] = raw_ypr[0];
}

void setup() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    Serial.begin(9600);
    -
    Serial1.begin(115200);

    mpu.initialize();
    mpu.dmpInitialize();

    mpu.setZGyroOffset(10); //64
    mpu.setZAccelOffset(1046); //724

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
    if(digitalRead(BUTTON_PIN) == LOW)
      AttachOffset();
    
    CulcDegData();
    Serial.println(DegData);
    
    Serial1.write(DegData);
}
