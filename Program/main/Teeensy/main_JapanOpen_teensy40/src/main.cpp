#include <Arduino.h>
#include <DSR1202.h>
#include <Adafruit_NeoPixel.h>
#include <U8g2lib.h>

#include "pid.h"
#include "timer.h"
#include "motor.h"
#include "kicker.h"
#include "button.h"
#include "sensors.h"
#include "neopixel.h"
#include "attacker.h"
#include "defencer.h"
#include "debug_program.h"

#define PIN_PRGB1 6
#define PIN_PRGB2 9

#define PIN_LCD_LEFT 33
#define PIN_LCD_RIGHT 31
#define PIN_LCD_DECIDE 30
#define PIN_LCD_PRGB 32

#define FIRST_FLOOR 0
#define SECOND_FLOOR 1
#define THIRD_FLOOR 2

#define LCD_TITLE_POINT_Y 16
#define LCD_CONTENT_POINT_Y 40

Kicker kicker(5, 4);
Button PRGB_1(PIN_PRGB1);
Button PRGB_2(PIN_PRGB2);

Button LCD_Decide(PIN_LCD_DECIDE);
Button LCD_Left(PIN_LCD_LEFT);
Button LCD_Right(PIN_LCD_RIGHT);
Button LCD_PRGB(PIN_LCD_PRGB);

U8G2_ST7565_AK_AQM1248_F_4W_HW_SPI u8g2(U8G2_R0, 10, 34, 35);

int SelectPos = 0;

#include "lcd.h"

void setup() {
  Serial.begin(115200);


  Initialize_Sensors();
  Initialize_NeoPixel();
  Initialize_LCD();
  NeoPixel_Off();

  dsr1202.Init();

  process_program = true;

  delay(3000);
}

void loop() {

  Read_Sensors();

  LCD_Decide.loop();
  LCD_Left.loop();
  LCD_Right.loop();

  if(LCD_Decide.isPushed())
  {
    process_program = !process_program;
  }

  if(process_program)
  {
    Attacker::Main_Program(SelectPos == 0);
  }
  else
  {
    NeoPixel_Off();
    Output_MotorPower(0, 0, 0, 0);
  }

  if(!process_program)
  {
    if(LCD_Left.isPushed())
    {
      SelectPos = max(SelectPos - 1, 0);
    }
    if(LCD_Right.isPushed())
    {
      SelectPos = min(SelectPos + 1, 2);
    }

    u8g2.clearBuffer();
    
    if(SelectPos == 0)
    {
      DrawString(0, 30, "TO YELLOW", u8g2_font_ncenB14_tr);
      DrawString(0, 45, String(Cam_GoalY_Dis).c_str(), u8g2_font_ncenB08_tr);
    }
    else if(SelectPos == 1)
    {
      DrawString(0, 30, "TO BLUE", u8g2_font_ncenB14_tr);
      DrawString(0, 45, String(Cam_GoalB_Dis).c_str(), u8g2_font_ncenB08_tr);
    }
    else if(SelectPos == 2)
    {
      DrawString(0, 15, (String("Y:") + String(Cam_GoalY_Deg) + String(":") + String(Cam_GoalY_Dis)).c_str(), u8g2_font_ncenB08_tr);
      DrawString(0, 30, (String("B:") + String(Cam_GoalB_Deg) + String(":") + String(Cam_GoalB_Dis)).c_str(), u8g2_font_ncenB08_tr);
      DrawString(0, 45, (String("I:") + String(Ball_Deg) + String(":") + String(Ball_Distance)).c_str(), u8g2_font_ncenB08_tr);
      DrawString(70, 30, (String("G:") + String(Gyro_Deg)).c_str(), u8g2_font_ncenB08_tr);
      DrawString(70, 45, (String("L:") + String(Line_Value)).c_str(), u8g2_font_ncenB08_tr);
    }

    Serial.println(Cam_GoalY_Dis);


    u8g2.sendBuffer();
  }
}