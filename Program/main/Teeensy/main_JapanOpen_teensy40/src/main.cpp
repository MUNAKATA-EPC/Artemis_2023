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

#define LCD_TITLE_POINT_Y 16
#define LCD_CONTENT_POINT_Y 40

bool process_program;

int Parents_Point;
int Now_Point;
int Now_Floor;

enum first_floor{
  PROGRAM,
  SENSORS,
  DEBUG
};

enum second_floor{
  //Parents floor : Programs
  ATTACKER = 0,
  DEFENCER = 1,
  PID_TEST = 2,
  KICKER = 3,
  BACK_TO_PROGRAM = 4,
  //Parents floor : Sensors
  BALLSENSOR = 10,
  LINESENSOR = 11,
  GYROSENSOR = 12,
  CAM_DATA = 13,
  BACK_TO_SENSORS = 13,
  //Parents floor : Debugs
  CHANGEMOTORSPEED = 20,
  CHECKBALLRANGE = 21,
  BACK_TO_DEBUG = 22,
};

enum third_floor{
  //Parents floor : Programs/Attacker
  ATTACK_IN_YELLOW = 0,
  ATTACK_IN_BLUE = 1,
  BACK_TO_ATTACK = 2,
  //Parents floor : Programs/Defencer
  DEFENCE_IN_YELLOW = 10,
  DEFENCE_IN_BLUE = 11,
  BACK_TO_DEFENCE = 12,
};

void setup() {
  Serial.begin(9600);

  Initialize_Sensors();
  Initialize_NeoPixel();
  Initialize_LCD();
  NeoPixel_Off();

  dsr1202.Init();

  process_program = false;
}

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
  LCD_PRGB.loop();

  if(Now_Floor == FIRST_FLOOR)
  {
    //内容を表示

    process_program = false;

    if(Now_Point == first_floor::PROGRAM)
    {
      DrawString(0, LCD_TITLE_POINT_Y, "Programs", u8g2_font_ncenB10_tr);
      
      if(LCD_Decide.isPushed())
      {
        Parents_Point = Now_Point;
        Now_Floor = SECOND_FLOOR;
        Now_Point = 0;
      }
    }
    else if(Now_Point == first_floor::SENSORS)
    {
      DrawString(0, LCD_TITLE_POINT_Y, "Sensors", u8g2_font_ncenB10_tr);
      
      if(LCD_Decide.isPushed())
      {
        Parents_Point = Now_Point;
        Now_Floor = SECOND_FLOOR;
        Now_Point = 0;
      }
    }
    else if(Now_Point == first_floor::DEBUG)
    {
      DrawString(0, LCD_TITLE_POINT_Y, "Debugs", u8g2_font_ncenB10_tr);

      /*
      if(LCD_Decide.isPushed())
      {
        Parents_Point = Now_Point;
        Now_Floor = SECOND_FLOOR;
        Now_Point = 0;
      }
      */
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

      if(Now_Point == second_floor::ATTACKER)
      {
        DrawString(0, LCD_TITLE_POINT_Y, "Programs/Attacker", u8g2_font_ncenB10_tr);
        DrawString(20, LCD_CONTENT_POINT_Y, "Yellow", u8g2_font_ncenB08_tr);
        DrawString(120, LCD_CONTENT_POINT_Y, "Blue", u8g2_font_ncenB08_tr);

        if(LCD_Decide.isPushed())
        {
          Parents_Point = Now_Point;
          Now_Floor = THIRD_FLOOR;
          Now_Point = 0;
        }
      }
      else if(Now_Point == second_floor::DEFENCER)
      {
        DrawString(0, LCD_TITLE_POINT_Y, "Programs/Defencer", u8g2_font_ncenB10_tr);
        DrawString(20, LCD_CONTENT_POINT_Y, "Yellow", u8g2_font_ncenB08_tr);
        DrawString(120, LCD_CONTENT_POINT_Y, "Blue", u8g2_font_ncenB08_tr);

        if(LCD_Decide.isPushed())
        {
          Parents_Point = Now_Point;
          Now_Floor = THIRD_FLOOR;
          Now_Point = 0;
        }
      }
      else if(Now_Point == second_floor::PID_TEST)
      {
        DrawString(0, LCD_TITLE_POINT_Y, "Programs/PID_Test", u8g2_font_ncenB10_tr);
        
        if(LCD_Decide.isPushed())
        {
          process_program = !process_program;
        }
      }
      else if(Now_Point == second_floor::KICKER)
      {
        DrawString(0, LCD_TITLE_POINT_Y, "Programs/Kicking_Test", u8g2_font_ncenB10_tr);

        if(LCD_Decide.isPushed())
        {
          process_program = !process_program;
        }
      }
      else if(Now_Point == second_floor::BACK_TO_PROGRAM)
      {
        DrawString(0, LCD_TITLE_POINT_Y, "Programs/BackToMain", u8g2_font_ncenB10_tr);
        DrawString(0, LCD_CONTENT_POINT_Y, "Back to before menu.", u8g2_font_ncenB08_tr);

        if(LCD_Decide.isPushed())
        {
          Now_Point = Parents_Point;
          Now_Floor = FIRST_FLOOR;
          Parents_Point = 0;
        }
      }

      //ボタン入力

      if(!process_program)
      {
        if(LCD_Left.isPushed())
        {
          Now_Point = ((Now_Point - 1) + 5) % 5;
        }
        if(LCD_Right.isPushed())
        {
          Now_Point = ((Now_Point + 1)) % 5;
        }
      }
    }
    else if(Parents_Point == first_floor::SENSORS)
    {
      process_program = false;

      //内容を表示
      
      if(Now_Point == second_floor::BALLSENSOR)
      {
        DrawString(0, LCD_TITLE_POINT_Y, "Sensors/Ball", u8g2_font_ncenB10_tr);
      }
      else if(Now_Point == second_floor::LINESENSOR)
      {
        DrawString(0, LCD_TITLE_POINT_Y, "Sensors/Line", u8g2_font_ncenB10_tr);
      }
      else if(Now_Point == second_floor::GYROSENSOR)
      {
        DrawString(0, LCD_TITLE_POINT_Y, "Sensors/Gyro", u8g2_font_ncenB10_tr);
      }
      else if(Now_Point == second_floor::CAM_DATA)
      {
        DrawString(0, LCD_TITLE_POINT_Y, "Sensors/Camera", u8g2_font_ncenB10_tr);
      }
      else if(Now_Point == second_floor::BACK_TO_SENSORS)
      {
        DrawString(0, LCD_TITLE_POINT_Y, "Sensors/BackToMain", u8g2_font_ncenB10_tr);
        DrawString(0, LCD_CONTENT_POINT_Y, "Back to before menu.", u8g2_font_ncenB08_tr);

        if(LCD_Decide.isPushed())
        {
          Now_Point = Parents_Point;
          Now_Floor = FIRST_FLOOR;
          Parents_Point = 0;
        }
      }

      //ボタン入力

      if(!process_program)
      {
        if(LCD_Left.isPushed())
        {
          Now_Point = 10 + (((Now_Point - 10) - 1) + 5) % 5;
        }
        if(LCD_Right.isPushed())
        {
          Now_Point = 10 + (((Now_Point - 10)  + 1)) % 5;
        }
      }
    }
    else if(Parents_Point == first_floor::DEBUG)
    {
      //内容を表示

      //ボタン入力
    }
  }
  else if(Now_Floor == THIRD_FLOOR)
  {
    if(Parents_Point == second_floor::ATTACKER)
    {
      //内容を表示

      if(Now_Point == third_floor::ATTACK_IN_YELLOW)
      {
        if(process_program)
        {
          Attacker::Main_Program(true);

          DrawString(0, LCD_TITLE_POINT_Y, "Processing...", u8g2_font_ncenB10_tr);
        }
        else
        {
          DrawString(0, LCD_TITLE_POINT_Y, "Programs/Attacker/In_Yellow", u8g2_font_ncenB10_tr);
          DrawString(0, LCD_CONTENT_POINT_Y, "My goal color is yellow, ok?", u8g2_font_ncenB08_tr);

          if(LCD_Decide.isPushed())
          {
            process_program = !process_program;
          }
        }
      }
      else if(Now_Point == third_floor::ATTACK_IN_BLUE)
      {
        if(process_program)
        {
          Attacker::Main_Program(false);

          DrawString(0, LCD_TITLE_POINT_Y, "Processing...", u8g2_font_ncenB10_tr);
        }
        else
        {
          DrawString(0, LCD_TITLE_POINT_Y, "Programs/Attacker/In_Blue", u8g2_font_ncenB10_tr);
          DrawString(0, LCD_CONTENT_POINT_Y, "My goal color is blue, ok?", u8g2_font_ncenB08_tr);

          if(LCD_Decide.isPushed())
          {
            process_program = !process_program;
          }
        }
      }
      else if(Now_Point == third_floor::BACK_TO_ATTACK)
      {
        DrawString(0, LCD_TITLE_POINT_Y, "Programs/Attacker/BackToMain", u8g2_font_ncenB10_tr);
        DrawString(0, LCD_CONTENT_POINT_Y, "Back to before menu.", u8g2_font_ncenB08_tr);
        
        if(LCD_Decide.isPushed())
        {
          Now_Point = Parents_Point;
          Now_Floor = FIRST_FLOOR;
          Parents_Point = first_floor::PROGRAM;
        }
      }

      //ボタン入力

      if(!process_program)
      {
        if(LCD_Left.isPushed())
        {
          Now_Point = ((Now_Point - 1) + 3) % 3;
        }
        if(LCD_Right.isPushed())
        {
          Now_Point = ((Now_Point + 1)) % 3;
        }
      }
    }
    else if(Parents_Point == second_floor::DEFENCER)
    {
      //内容を表示

      if(Now_Point == third_floor::ATTACK_IN_YELLOW)
      {
        if(process_program)
        {
          Defencer::Main_Program(true);

          DrawString(0, LCD_TITLE_POINT_Y, "Processing...", u8g2_font_ncenB10_tr);
        }
        else
        {
          DrawString(0, LCD_TITLE_POINT_Y, "Programs/Defencer/In_Yellow", u8g2_font_ncenB10_tr);
          DrawString(0, LCD_CONTENT_POINT_Y, "My goal color is yellow, ok?", u8g2_font_ncenB08_tr);

          if(LCD_Decide.isPushed())
          {
            process_program = !process_program;
          }
        }
      }
      else if(Now_Point == third_floor::ATTACK_IN_BLUE)
      {
        if(process_program)
        {
          Defencer::Main_Program(true);

          DrawString(0, LCD_TITLE_POINT_Y, "Processing...", u8g2_font_ncenB10_tr);
        }
        else
        {
          DrawString(0, LCD_TITLE_POINT_Y, "Programs/Defencer/In_Yellow", u8g2_font_ncenB10_tr);
          DrawString(0, LCD_CONTENT_POINT_Y, "My goal color is yellow, ok?", u8g2_font_ncenB08_tr);

          if(LCD_Decide.isPushed())
          {
            process_program = !process_program;
          }
        }
      }
      else if(Now_Point == third_floor::BACK_TO_DEFENCE)
      {
        DrawString(0, LCD_TITLE_POINT_Y, "Programs/Attacker/BackToMain", u8g2_font_ncenB10_tr);
        DrawString(0, LCD_CONTENT_POINT_Y, "Back to before menu.", u8g2_font_ncenB08_tr);
        
        if(LCD_Decide.isPushed())
        {
          Now_Point = Parents_Point;
          Now_Floor = FIRST_FLOOR;
          Parents_Point = first_floor::PROGRAM;
        }
      }

      //ボタン入力

      if(!process_program)
      {
        if(LCD_Left.isPushed())
        {
          Now_Point = 10 + (((Now_Point - 10) - 1) + 3) % 3;
        }
        if(LCD_Right.isPushed())
        {
          Now_Point = (((Now_Point - 10) + 1)) % 3;
        }
      }
    }
  }

  delay(10);
}