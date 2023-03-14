#include <Arduino.h>
#include <DSR1202.h>

#include "pid.h"
#include "motor.h"
#include "timer.h"
#include "sensors.h"
#include "kicker.h"
#include "mainprogram.h"

Kicker kicker(5, 4);

#define FIRST_FLOOR 0
#define SECOND_FLOOR 1
#define THIRD_FLOOR 2

#define PRGB1 6
#define PRGB2 9

int Parents_Point;
int Now_Point;
int Now_Floor;

enum first_floor{
  PROGRAM,
  SENSORS,
  DEBUG
};

enum second_floor{
  //Parents floor : Program
  MAINPROGRAM = 0,
  KICKER = 1,
  LINE = 2,
  BACK_TO_PROGRAM = 3,
  //Parents floor : Sensor
  BALLSENSOR = 10,
  GYROSENSOR = 11,
  LINESENSOR = 12,
  BACK_TO_SENSORS = 13,
  //Parents floor : Debug
  CHANGEMOTORSPEED = 20,
  CHECKBALLRANGE = 21,
  BACK_TO_DEBUG = 22,
};

void setup() {
  Serial.begin(115200);

  Initialize_Sensors();

  pinMode(PRGB1, INPUT_PULLUP);
  pinMode(PRGB2, INPUT_PULLUP);

  dsr1202.Init();
}

void loop() {
  Read_Sensors();

  Main_Program();

  if(Now_Floor == FIRST_FLOOR)
  {
    //内容を表示

    //ボタン入力
  }
  else if(Now_Floor == SECOND_FLOOR)
  {
    if(Parents_Point == first_floor::PROGRAM)
    {
      //内容を表示
      
      //ボタン入力

    }
    else if(Parents_Point == first_floor::SENSORS)
    {
      //内容を表示

      //ボタン入力
    }
    else if(Parents_Point == first_floor::DEBUG)
    {
      //内容を表示

      //ボタン入力
    }
  }
  else if(Now_Floor == THIRD_FLOOR)
  {
    if(Parents_Point == second_floor::MAINPROGRAM)
    {
      //内容を表示

      //ボタン入力
    }
  }
}