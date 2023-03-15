#include <Arduino.h>

int LINE_Theta[] = {360, 90, 90, 180, 180, 270, 270};
int LINE_Pin[] = {0, 1, 2, 3, 4, 5, 6};
// 0 : none / 1 : through
int LINE_State[7];
int First_Pos;
int First_deg;
int Now_Line_Deg;

int Line_Deg;

void setup() {
  Serial2.begin(115200);
}

void loop() {
  if(CheckAllLine() == false)
  {
    Line_Deg = 0;
    for(int i = 0; i < 7; i++)
    {
      if(digitalRead(LINE_Pin[i]) == LOW)
      {
          First_Pos = i;
          First_deg = LINE_Theta[i] == 360 ? 0 : LINE_Theta[i];
          LINE_State[i] = 1;
      }
    }
    Serial2.println(-1);
  }
  else
  {
    int Line_Count;
    for(int i = 0; i < 7; i++)
    {
      if(digitalRead(i) == 1)
      {
        Line_Count++;
        Now_Line_Deg += LINE_Theta[i];
      }
    }
    Now_Line_Deg = (Now_Line_Deg % 360) / Line_Count;
    
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
      if(First_deg - 45 <= Now_Line_Deg || Now_Line_Deg <= First_deg + 45)
      {
        Line_Deg = Now_Line_Deg;
      }
      else
      {
        Line_Deg = First_deg;
      }
    }
  }
  Serial2.println(Line_Deg);
}

bool CheckAllLine(){
  bool ret = false;
  for(int i = 0; i < 7; i++)
  {
    if(digitalRead(i) == 1)
    {
      ret = true;
    }
  }
  return ret;
}