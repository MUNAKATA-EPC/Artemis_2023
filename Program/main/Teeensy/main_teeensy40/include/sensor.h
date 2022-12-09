#define IR_Permission 920

int ball_deg;
int ball_distance;
int Gyro_deg;
int LINE_value;

int court_deg;

typedef struct{
    int index;  //IRセンサ識別番号
    int value;  //IRセンサ値
}IR_SENSOR;

IR_SENSOR ir_sen[8];

int _ir_pin[8] = { 4, 5, 8, 9, 10, 11, 12, 13 };    //IRセンサ接続ピン

int CompareIRValue(const void* n1, const void* n2){
  if(((IR_SENSOR*)n1)->value < ((IR_SENSOR*)n2)->value)
    return -1;
  else if(((IR_SENSOR*)n1)->value > ((IR_SENSOR*)n2)->value)
    return 1;
  else 
    return 0;
}

void Setup_Sensors(){
    Serial2.begin(112500);  //Gyro
    Serial3.begin(112500);  //LINE
    Serial4.begin(112500);  //Camera
}

void Read_IR(){
  for(int i = 0; i < 8; i++){
      ir_sen[i].index = i + 1;
      ir_sen[i].value = analogRead(_ir_pin[i]);
  }

  qsort(ir_sen, sizeof(ir_sen) / sizeof(ir_sen[0]), sizeof(IR_SENSOR), CompareIRValue);

  if(ir_sen[0].value < IR_Permission){
    if(ir_sen[0].index == 8 && ir_sen[1].index == 1)  //IRの場所が1番目の場合{
      ball_deg = 1;
    else if(ir_sen[0].index == 1 && ir_sen[1].index == 8)  //IRの場所が1番目の場合
      ball_deg = 1;
    else if(ir_sen[0].index > ir_sen[1].index) //一番反応しているIRの場所が二番目より右側の場合
      ball_deg = ir_sen[0].index * 2 - 1;
    else if(ir_sen[0].index < ir_sen[1].index) //一番反応しているIRの場所が二番目より左側の場合
      ball_deg = ir_sen[0].index * 2;

    ball_distance = (ir_sen[0].value + ir_sen[1].value) / 2;
  }
}

void Read_Gyro(){
    Gyro_deg = Serial2.read();
}

void Read_LINE(){
    LINE_value = Serial3.read();
}

void Read_Camera(){
  if(Serial4.available() != 0){
    if(Serial4.read() == 255) {
      Serial.println(Serial4.read());
    }
  }
}