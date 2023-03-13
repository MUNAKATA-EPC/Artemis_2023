#define BUTTON_PIN 0

bool dmpReady = false;  // set true if DMP init was successful
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint8_t fifoBuffer[64]; // FIFO storage buffer

float ypr[3], raw_ypr[3], offset_ypr[3];           //yaw   yaw/pitch/roll container and gravity vector

int Gyro_Degree;

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
  
  Gyro_Degree = ypr[0] * 180 / M_PI;
  if(Gyro_Degree < 0)
    Gyro_Degree = Gyro_Degree + 360;
}

//Initialize Degree Of Robot
void AttachOffset(){
  offset_ypr[0] = raw_ypr[0];
}

void MPU6050_setup() {
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
    #endif
    
    //MPU6050の初期化
    //分解能の指定ができるように改造 MPU6050_GYRO_FS_????
    mpu.initialize(MPU6050_IMU::MPU6050_GYRO_FS_2000);
    mpu.dmpInitialize();

    //オフセット、キャリブレーション値を設定
    mpu.setZGyroOffset(47); //64
    mpu.setZAccelOffset(560); //724

    mpu.CalibrateAccel(6);
    mpu.CalibrateGyro(6);
    mpu.PrintActiveOffsets();
    
    mpu.setDMPEnabled(true);

    dmpReady = true;
}

void MPU6050_loop() {
    if(analogRead(BUTTON_PIN) <= 1000)
      AttachOffset();
    
    CulcDegData();
    
    Serial.print(analogRead(BUTTON_PIN));
    Serial.print("\t");
    Serial.println(Gyro_Degree);
}
