int LINE_Theta[] = {0, 90, 90, 270, 270, 180, 180};
int LINE_Pin[] = {0, 1, 2, 3, 4, 5, 6};
// 0 : none / 1 : through
int LINE_State[7];
int First_Pos = 0;
int First_deg = 0;
int Now_Line_Deg = 0;
bool Line_Now;

int Line_Deg = 0;

void setup() {
  Serial1.begin(115200);
}

void loop() {
  for(int i = 0; i < 7; i++)
  {
    int val = analogRead(LINE_Pin[i]);
    LINE_State[i] = val <= 400 ? 1 : 0;
  }

  if(GetSensorCount() == 0)
  {
    Line_Now = false;
    Line_Deg = 0;
    Serial1.println("-1");
  }
  else
  {
    if(GetSensorCount() == 1)
    {      
      for(int i = 0; i < 7; i++)
      {
        if(LINE_State[i] == 1)
        {
            if(!Line_Now)
            {
              First_Pos = i;
              First_deg = LINE_Theta[i];
              Line_Deg = First_deg;
            }
            else
            {
              Line_Deg = First_deg;
            }
            Line_Now = true;
            
            Serial1.println(Line_Deg);
            Serial1.flush();
            break;
        }
      }
    }
    else
    {
        Line_Now = true;
        Now_Line_Deg = 0;
        int Line_Count = 0;
        bool readed[3] = {false, false, false};
        for(int i = 0; i < 7; i++)
        {
          if(LINE_State[i] == 1)
          {
            if(i == 0 ||
            ((i == 1 || i == 2) && !readed[0]) ||
            ((i == 3 || i == 4) && !readed[1]) ||
            ((i == 5 || i == 6) && !readed[2]))
            {
              Line_Count++;
              Now_Line_Deg += LINE_Theta[i];
              
              if(i == 1 || i == 2)
                readed[0] = true;
              else if(i == 3 || i == 4)
                readed[1] = true;
              else if(i == 5 || i == 6)
                readed[2] = true;
            }
          }
        }
        
        Now_Line_Deg = Now_Line_Deg > 450 ? (Now_Line_Deg % 360) / Line_Count : Now_Line_Deg / Line_Count;
                
        if(First_deg == 0)
        {
          if(360 - 45 <= Now_Line_Deg || Now_Line_Deg <= 0 + 45)
          {
            Line_Deg = Now_Line_Deg;
          }
          else
          {
            Line_Deg = First_deg;
          }
        }
        else
        {
          if(First_deg - 45 <= Now_Line_Deg && Now_Line_Deg <= First_deg + 45)
          {
            Line_Deg = Now_Line_Deg;
          }
          else
          {
            Line_Deg = First_deg;
          }
        }
    
        Serial1.println(Line_Deg);
        Serial1.flush();
    }
  }
}

bool CheckAllLine(){
  bool ret = false;
  for(int i = 0; i < 7; i++)
  {
    if(LINE_State[i] == 1)
    {
      ret = true;
    }
  }
  return ret;
}

int GetSensorCount()
{
    int retu = 0;
    for(int i = 0; i < 7; i++)
    {
       if(LINE_State[i] == 1)
       {
          retu++;
       }
    }
    return retu;
}
