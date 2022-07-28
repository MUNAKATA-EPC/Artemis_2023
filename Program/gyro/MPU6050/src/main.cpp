#include <Arduino.h>
#include <Wire.h>

// MPU-6050のアドレス、レジスタ設定値
#define MPU6050_WHO_AM_I     0x75  // Read Only
#define MPU6050_PWR_MGMT_1   0x6B  // Read and Write
#define MPU_ADDRESS  0x68

#define CAL_TIMEMS 1000
#define DELAY_MS   10

#define OUTPUT_PIN 0
#define BUTTON_PIN 2

int current_time;
int last_time;

float deg;
float cal_val;

bool DoCalibration;

void Update();
void ReadGyro();
void Calibration(int timems);

// デバイス初期化時に実行される
void setup() {
  analogWriteResolution(10);

  Serial.begin(9600);
  Wire.begin();

  pinMode(BUTTON_PIN, INPUT);

  // 初回の読み出し
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(MPU6050_WHO_AM_I);  //MPU6050_PWR_MGMT_1
  Wire.write(0x00);
  Wire.endTransmission();

  // 動作モードの読み出し
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(MPU6050_PWR_MGMT_1);  //MPU6050_PWR_MGMT_1レジスタの設定
  Wire.write(0x00);
  Wire.endTransmission();

  Calibration(5000);
}

void loop() {
  ReadGyro();

  if(analogRead(BUTTON_PIN) >= 1020){
    Calibration(CAL_TIMEMS);
  }

  long output_data = (deg / 36000) * 1023;

  analogWrite(OUTPUT_PIN, output_data);

  delay(DELAY_MS);

  Serial.print(cal_val);
  Serial.print(" ");
  Serial.print(output_data);
  Serial.print(" ");
  Serial.println(analogRead(2));
}

///MPU6050の値を読み取り、度数法に計算し直します。
void ReadGyro(){
  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 14, true);
  
  current_time = micros();
  int data[14];
  int i = 0;
  while (Wire.available()){
    data[i++] = Wire.read();
  }

  int16_t gxRaw = data[12] << 8 | data[13];

  float gyro_x = gxRaw / 131.0;   //FS_SEL_0 131 LSB / (°/s)

  if(DoCalibration)
  {
    deg += (gyro_x) * ((current_time - last_time)) / 10000.0;
  }
  else
  {
    deg += (gyro_x - cal_val) * ((current_time - last_time)) / 10000.0;

    if(deg >= 36000)
      deg = 0;
    else if(deg < 0)
      deg = 36000;
  }

  last_time = current_time;
}

void Calibration(int timems){
  DoCalibration = true;   //キャリブレーション中かどうかの判定変数
  deg = 0;

  for(int i = 0; i < (timems / DELAY_MS); i++)
  {
    ReadGyro();
    delay(DELAY_MS);
  }

  cal_val = deg / (float)(timems / DELAY_MS);

  DoCalibration = false;
  deg = 0;
}