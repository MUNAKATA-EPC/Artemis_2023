//  [-4827,-4826] --> [-15,2]	[-1149,-1148] --> [-9,9]	[517,518] --> [16374,16399]	[85,86] --> [-1,2]	[10,11] --> [-1,3]	[34,35] --> [-2,1]

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
  mpuIntStatus = mpu.getIntStatus();
  if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
    mpu.resetFIFO();
    delay(10);
  }

  while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
  
  fifoBuffer[64];
  mpu.getFIFOBytes(fifoBuffer, packetSize);
  fifoCount -= packetSize;

  Quaternion _quaternion;
  VectorFloat _gravity;
  mpu.dmpGetQuaternion(&_quaternion, fifoBuffer);
  mpu.dmpGetGravity(&_gravity, &_quaternion);
  mpu.dmpGetYawPitchRoll(raw_ypr, &_quaternion, &_gravity);

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

    Wire.begin();
    Wire.setClock(400000);

    Serial.begin(9600);
    Serial1.begin(115200);

    mpu.initialize();
    mpu.dmpInitialize();
    mpu.setDMPEnabled(true);

    mpu.setXGyroOffset(-30); //64
    mpu.setYGyroOffset(29); //64
    mpu.setZGyroOffset(15); //64
    mpu.setZAccelOffset(1596); //724

    mpuIntStatus = mpu.getIntStatus();
    packetSize = mpu.dmpGetFIFOPacketSize();
}

void loop() {
    if(digitalRead(BUTTON_PIN) == LOW)
      AttachOffset();
    
    CulcDegData();

    Serial.println(DegData);
    
    Serial1.write(DegData);
    Serial1.flush();
}
