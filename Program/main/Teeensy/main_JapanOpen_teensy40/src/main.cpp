#include <Arduino.h>
#include <DSR1202.h>
#include <Adafruit_NeoPixel.h>
#include <U8g2lib.h>

#include "timer.h"
#include "kicker.h"
#include "button.h"
#include "sensors.h"

#define PIN_PRGB1 6
#define PIN_PRGB2 9

#define PIN_LCD_LEFT 33
#define PIN_LCD_RIGHT 31
#define PIN_LCD_DECIDE 30
#define PIN_LCD_PRGB 32

Kicker kicker(5, 4);
Button PRGB_1(PIN_PRGB1);
Button PRGB_2(PIN_PRGB2);

Button LCD_Decide(PIN_LCD_DECIDE);
Button LCD_Left(PIN_LCD_LEFT);
Button LCD_Right(PIN_LCD_RIGHT);
Button LCD_PRGB(PIN_LCD_PRGB);

U8G2_ST7565_AK_AQM1248_F_4W_HW_SPI u8g2(U8G2_R0, 10, 34, 35);

#include "pid.h"
#include "lcd.h"
#include "motor.h"
#include "neopixel.h"
#include "mainprogram.h"

#define FIRST_FLOOR 0
#define SECOND_FLOOR 1
#define THIRD_FLOOR 2

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
  Serial.begin(9600);

  Initialize_Sensors();
  Initialize_NeoPixel();
  Initialize_LCD();
  NeoPixel_Off();

  dsr1202.Init();
}

bool process_program;

void loop() {
  /*
  PRGB_1.loop();
  PRGB_2.loop();

  if(PRGB_1.isPushed())
  {
    process_program = !process_program;
  }

  Read_Sensors();

  if(process_program)
  {
    Main_Program();
  }
  else
  {
    NeoPixel_Off();
    Break();
  }
  */

  LCD_Left.loop();
  LCD_Right.loop();
  LCD_Decide.loop();

  if(Now_Floor == FIRST_FLOOR)
  {
    //内容を表示

    if(Now_Point == 0)
    {
      DrawString(0, 17, "Programs", u8g2_font_ncenB10_tr);
    }
    else if(Now_Point == 1)
    {
      DrawString(0, 17, "Check Sensors", u8g2_font_ncenB10_tr);
    }
    else if(Now_Point == 2)
    {
      DrawString(0, 17, "Robot Debugs", u8g2_font_ncenB10_tr);
    }

    //ボタン入力

    if(LCD_Left.isPushed())
    {
      Now_Point = ((Now_Point - 1) + 3) % 3;
    }
    if(LCD_Right.isPushed())
    {
      Now_Point = ((Now_Point + 1)) % 3;
    }
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

  delay(10);
}