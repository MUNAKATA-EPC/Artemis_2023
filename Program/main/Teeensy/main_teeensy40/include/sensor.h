void Setup_Sensors(){
    Serial2.begin(112500);  //Gyro
    Serial3.begin(112500);  //LINE
    Serial4.begin(112500);  //Camera
}

// 円形ボールセンサ
typedef struct{
    int index;  //IRセンサ識別番号
    int value;  //IRセンサ値
}IR_SENSOR;

int _ir_pin[8] = { 4, 5, 8, 9, 10, 11, 12, 13 };    //IRセンサ接続ピン

int ball_deg;
int ball_distance;

IR_SENSOR ir_sen[8];

void Read_IR(){
}

//ジャイロセンサ
int Gyro_value;

void Read_Gyro(){
    Gyro_value = Serial2.read();
}

int LINE_value;

void Read_LINE(){
    LINE_value = Serial3.read();
}

int court_deg;
int court_distance;
int goal_deg_yellow;
int goal_distance_yellow;
int goal_deg_blue;
int goal_distance_blue;

void Read_Camera(){
  if(Serial4.available() != 0) {
    if(Serial4.read() == 255) {
      //Serial.println(Serial4.read());
    }
  }
}