#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>

#define OUTPUT_PIN 0
#define PWM_PIN 1

//IR_SENSORの許可できる最大反応値を代入します。
const int PermissionRange = 920;    //about 90% (1024 * 0.9)
int BallDeg;                        //最終出力時のボールの角度
int BallDistance;                   //最終出力時のボールの距離

typedef struct{
  int index;
  int value;
} IR_SENSOR;

IR_SENSOR IR_Sen[8];

void Read_IR(); 
int OutputValue(int index);

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

void setup() {
  analogWriteResolution(10);  //0-255 to 0~1023

  for(int i = 2; i < 2 + 8; i++){
    pinMode(i, INPUT);
  }

  Serial.begin(9600);
}

void loop() {
  Read_IR();

  //qsort関数により配列の値を降順ソートします。
  qsort(IR_Sen, sizeof(IR_Sen) / sizeof(IR_Sen[0]), sizeof(IR_SENSOR), CompareIRValue);

  //降順ソートした場合に、センサーの値が許容範囲値におさまっている場合、各電圧を出力します。
  if(IR_Sen[0].value < PermissionRange){
    if(IR_Sen[0].index == 8 && IR_Sen[1].index == 1)  //IRの場所が1番目の場合{
      BallDeg = 1;
    else if(IR_Sen[0].index == 1 && IR_Sen[1].index == 8)  //IRの場所が1番目の場合
      BallDeg = 1;
    else if(IR_Sen[0].index > IR_Sen[1].index) //一番反応しているIRの場所が二番目より右側の場合
      BallDeg = IR_Sen[0].index * 2 - 1;
    else if(IR_Sen[0].index < IR_Sen[1].index) //一番反応しているIRの場所が二番目より左側の場合
      BallDeg = IR_Sen[0].index * 2;

    BallDistance = (IR_Sen[0].value + IR_Sen[1].value) / 2;
    analogWrite(OUTPUT_PIN,  OutputValue(BallDeg));
  }
  else { //許容範囲値におさまっていなかった場合、最大電圧値を出力します。
    BallDeg = 0;
    analogWrite(OUTPUT_PIN, 1023);
  }

  Serial.println(IR_Sen[0].value);

  delay(10);
}


//各ポートのIRセンサーの値を読み取り、構造体のvalue変数に代入します。
void Read_IR(){
  for(int i = 1; i < 9; i++){
    IR_Sen[i].index = i + 1;    //毎ループごとに配列のIndex値が変化するので代入。
    IR_Sen[i].value = analogRead(i + 1);
  }
}

//Index値によるアウトプット値の計算。(TJ3B側ではMax64%となる。)
//0-64%の時、各Index値により公差4%、最大値64(4*16)%。
int OutputValue(int index){
  return 936 / 16 * index;
}