#include <Arduino.h>

//Wireライブラリのinclude
#include <Wire.h>

// MPU-6050のアドレス、レジスタ設定値
#define MPU6050_WHO_AM_I     0x75   //読み取り専用
#define MPU6050_PWR_MGMT_1   0x6B   //読み書き
#define MPU_ADDRESS  0x68           //レジスタアドレス

#define OUTPUT_PIN 0                //アウトプットピンの指定
#define RESET_BUTTON 2              //リセットピンのポート指定

#define CAL_TIME 1                  //キャリブレーションタイムの指定
#define DELAY_TIME 10

volatile uint8_t data[14];          //センサからのデータ格納用配列

int current_time;                   //前回読み込み時の時間取得起動時の時間
int last_time;                      //現在の時間取得

//MPU6050からのデータ読み込み
void ReadData(){
    Wire.beginTransmission(0x68);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(0x68, 14, true);

    static int i = 0;
    while (Wire.available()) {
        data[i++] = Wire.read();      //データを読み込む
    }

    int16_t gxRaw = data[12] << 8 | data[13];   //角速度の生データ取得

    current_time = micros();                    //現在の時間を代入

    last_time = current_time;                   //前回の時間保存変数に現在の時間を代入

    Serial.println(gxRaw);
}

void setup() {
    Wire.begin();                   //Wireライブラリの使用開始
    Serial.begin(9600);             //PCとの通信を開始

    //ピンモード指定
    pinMode(OUTPUT_PIN, OUTPUT);
    pinMode(RESET_BUTTON, INPUT);

    current_time = micros();        //現在の時間取得
}

void loop() {
    ReadData();

    if(digitalRead(RESET_BUTTON) == HIGH)
    {
        Serial.println(digitalRead(RESET_BUTTON));
    }
}