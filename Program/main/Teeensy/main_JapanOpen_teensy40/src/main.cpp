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
#include "mainprogram.h"
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

#include "lcd.h"

void setup() {
  Serial.begin(115200);

  Initialize_Sensors();
  Initialize_NeoPixel();
  Initialize_LCD();
  NeoPixel_Off();

  dsr1202.Init();

  process_program = false;
}

void loop() {

  Read_Sensors();
  
  Attacker::Main_Program(true);
  
  u8g2.clearBuffer();
  DrawString(0, 15, String(Ball_Deg).c_str(), u8g2_font_ncenB12_tr);
  u8g2.sendBuffer();
  
  //Process_LCD();
}