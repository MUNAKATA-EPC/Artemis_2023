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
  LINE_TEST = 3,
  BACK_TO_PROGRAM = 4,  //Parents floor : Sensors
  BALLSENSOR = 10,
  LINESENSOR = 11,
  GYROSENSOR = 12,
  CAM_DATA = 13,
  BACK_TO_SENSORS = 14,
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

void DrawString(int x, int y, const char *text, const uint8_t* font)
{
    u8g2.setFont(font);
    u8g2.drawStr(x, y, text);
}

void Initialize_LCD()
{
    u8g2.begin(); //LCD初期化
    u8g2.setFlipMode(0);  //反転は1(通常表示は0)
    u8g2.setContrast(0);
}

void Process_LCD()
{
  u8g2.clearBuffer();

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
        Now_Point = 10;
      }
    }
    else if(Now_Point == first_floor::DEBUG)
    {
      DrawString(0, LCD_TITLE_POINT_Y, "Debugs", u8g2_font_ncenB10_tr);

      if(LCD_Decide.isPushed())
      {
        Parents_Point = Now_Point;
        Now_Floor = SECOND_FLOOR;
        Now_Point = 20;
      }
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
        DrawString(0, LCD_TITLE_POINT_Y, "Programs/Attacker", u8g2_font_ncenB08_tr);

        if(LCD_Decide.isPushed())
        {
          Parents_Point = Now_Point;
          Now_Floor = THIRD_FLOOR;
          Now_Point = 0;
        }
      }
      else if(Now_Point == second_floor::DEFENCER)
      {
        DrawString(0, LCD_TITLE_POINT_Y, "Programs/Defencer", u8g2_font_ncenB08_tr);

        if(LCD_Decide.isPushed())
        {
          Parents_Point = Now_Point;
          Now_Floor = THIRD_FLOOR;
          Now_Point = 10;
        }
      }
      else if(Now_Point == second_floor::PID_TEST)
      {
        DrawString(0, LCD_TITLE_POINT_Y, "Programs/PID_Test", u8g2_font_ncenB08_tr);
        
        if(process_program)
        {
          PID_PROG::Main_Program();
          DrawString(0, LCD_CONTENT_POINT_Y + 10, "Processing...", u8g2_font_ncenB10_tr);
        }
        else
        {
          NeoPixel_Off();
          Output_MotorPower(0, 0, 0, 0);
        }

        if(LCD_Decide.isPushed())
        {
          process_program = !process_program;
        }
      }
      else if(Now_Point == second_floor::LINE_TEST)
      {
        DrawString(0, LCD_TITLE_POINT_Y, "Programs/Line_Test", u8g2_font_ncenB08_tr);

        if(process_program)
        {
          LINE_PROG::Main_Program();
          DrawString(0, LCD_CONTENT_POINT_Y + 10, "Processing...", u8g2_font_ncenB10_tr);
        }

        if(LCD_Decide.isPushed())
        {
          process_program = !process_program;
          NeoPixel_Off();
          Output_MotorPower(0, 0, 0, 0);
        }
      }
      else if(Now_Point == second_floor::BACK_TO_PROGRAM)
      {
        DrawString(0, LCD_TITLE_POINT_Y, "Programs/BackToMain", u8g2_font_ncenB08_tr);
        DrawString(0, LCD_CONTENT_POINT_Y, "Back to before menu.", u8g2_font_6x10_tr);

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
        DrawString(0, LCD_TITLE_POINT_Y, "BallRing", u8g2_font_ncenB10_tr);
        DrawString(7, 31, (String("Deg:") + String(Ball_Deg == 510 ? "NaN" : String(Ball_Deg))).c_str(), u8g2_font_6x10_tr);
        DrawString(7, 43, (String("Dis:") + String(Ball_Distance == 255 ? "NaN" : String(Ball_Distance))).c_str(), u8g2_font_6x10_tr);

        u8g2.drawCircle(100, 25, 6);
        u8g2.drawLine(100, 2, 100, 48);

        u8g2.drawLine(77, 25, 123, 25);

        if(Ball_Deg != 510 && Ball_Distance != 255)
        {
          double ball_distance = min(max((Ball_Distance - 30) / 50.0 * 20.0, 0), 15);
          double ball_pos[2] = {cos(radians(Ball_Deg - 90)) * ball_distance, sin(radians(Ball_Deg - 90)) * ball_distance};
          u8g2.drawDisc(100 + ball_pos[0], 25 + ball_pos[1], 2);
        }
      }
      else if(Now_Point == second_floor::LINESENSOR)
      {
        DrawString(0, LCD_TITLE_POINT_Y, "Line", u8g2_font_ncenB10_tr);
        DrawString(7, 37, (String("Deg:") + String(Line_Value)).c_str(), u8g2_font_6x13B_tr);
      }
      else if(Now_Point == second_floor::GYROSENSOR)
      {
        DrawString(0, LCD_TITLE_POINT_Y, "Gyro", u8g2_font_ncenB10_tr);
        DrawString(7, 37, (String("Deg:") + String(Gyro_Deg)).c_str(), u8g2_font_6x13B_tr);
      }
      else if(Now_Point == second_floor::CAM_DATA)
      {
        DrawString(0, LCD_TITLE_POINT_Y, "Camera", u8g2_font_ncenB10_tr);
        
        DrawString(0, LCD_CONTENT_POINT_Y, String(Cam_GoalY_Deg).c_str(), u8g2_font_6x13B_tr);
      }
      else if(Now_Point == second_floor::BACK_TO_SENSORS)
      {
        DrawString(0, LCD_TITLE_POINT_Y, "Sensors/BackToMain", u8g2_font_ncenB08_tr);
        DrawString(0, LCD_CONTENT_POINT_Y, "Back to before menu.", u8g2_font_6x13_tr);

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
          Now_Point = 10 + (((Now_Point - 10) + 1)) % 5;
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
          
          if(LCD_Decide.isPushed())
          {
            process_program = !process_program;
            NeoPixel_Off();
            Output_MotorPower(0, 0, 0, 0);
          }
        }
        else
        {
          DrawString(0, LCD_TITLE_POINT_Y, ".../Attacker/Yellow", u8g2_font_6x13B_tr);
          DrawString(0, LCD_CONTENT_POINT_Y, "In yellow, ok?", u8g2_font_6x12_tr);

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
          
          if(LCD_Decide.isPushed())
          {
            process_program = !process_program;
            NeoPixel_Off();
            Output_MotorPower(0, 0, 0, 0);
          }
        }
        else
        {
          DrawString(0, LCD_TITLE_POINT_Y, ".../Attacker/Blue", u8g2_font_6x13B_tr);
          DrawString(0, LCD_CONTENT_POINT_Y, "In blue, ok?", u8g2_font_6x12_tr);

          if(LCD_Decide.isPushed())
          {
            process_program = !process_program;
          }
        }
      }
      else if(Now_Point == third_floor::BACK_TO_ATTACK)
      {
        DrawString(0, LCD_TITLE_POINT_Y, ".../Attacker/Back", u8g2_font_6x13B_tr);
        DrawString(0, LCD_CONTENT_POINT_Y, "Back to before menu.", u8g2_font_ncenB08_tr);
        
        if(LCD_Decide.isPushed())
        {
          Now_Point = Parents_Point;
          Now_Floor = SECOND_FLOOR;
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

      if(Now_Point == third_floor::DEFENCE_IN_YELLOW)
      {
        if(process_program)
        {
          Defencer::Main_Program(true);

          DrawString(0, LCD_TITLE_POINT_Y, "Processing...", u8g2_font_ncenB10_tr);
          
          if(LCD_Decide.isPushed())
          {
            process_program = !process_program;
            NeoPixel_Off();
            Output_MotorPower(0, 0, 0, 0);
          }
        }
        else
        {
          DrawString(0, LCD_TITLE_POINT_Y, ".../Defencer/Yellow", u8g2_font_6x13B_tr);
          DrawString(0, LCD_CONTENT_POINT_Y, "In yellow, ok?", u8g2_font_6x12_tr);

          if(LCD_Decide.isPushed())
          {
            process_program = !process_program;
          }
        }
      }
      else if(Now_Point == third_floor::DEFENCE_IN_BLUE)
      {
        if(process_program)
        {
          Defencer::Main_Program(false);

          DrawString(0, LCD_TITLE_POINT_Y, "Processing...", u8g2_font_ncenB10_tr);
          
          if(LCD_Decide.isPushed())
          {
            process_program = !process_program;
            NeoPixel_Off();
            Output_MotorPower(0, 0, 0, 0);
          }
        }
        else
        {
          DrawString(0, LCD_TITLE_POINT_Y, ".../Defencer/Blue", u8g2_font_6x13B_tr);
          DrawString(0, LCD_CONTENT_POINT_Y, "In blue, ok?", u8g2_font_6x12_tr);

          if(LCD_Decide.isPushed())
          {
            process_program = !process_program;
          }
        }
      }
      else if(Now_Point == third_floor::BACK_TO_DEFENCE)
      {
        DrawString(0, LCD_TITLE_POINT_Y, ".../Defencer/Back", u8g2_font_6x13B_tr);
        DrawString(0, LCD_CONTENT_POINT_Y, "Back to before menu.", u8g2_font_6x12_tr);
        
        if(LCD_Decide.isPushed())
        {
          Now_Point = Parents_Point;
          Now_Floor = SECOND_FLOOR;
          Parents_Point = first_floor::PROGRAM;
        }
      }

      //ボタン入力

      if(!process_program)
      {
        if(LCD_Left.isPushed())
        {
          Now_Point = 10 + ((((Now_Point - 10) - 1) + 3) % 3);
        }
        if(LCD_Right.isPushed())
        {
          Now_Point = 10 + ((((Now_Point - 10) + 1)) % 3);
        }
      }
    }
  }
  
  u8g2.sendBuffer();
}