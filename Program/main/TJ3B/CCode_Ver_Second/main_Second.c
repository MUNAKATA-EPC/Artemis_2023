//--------------------------------------------------------------------------------
// Title: Main - [ main_Second.c ]
// Build:DAISEN C-Style for TJ3B  [ Ver.20190706 ] - [ Build_V190617 ]
//--------------------------------------------------------------------------------
// SetupVal:111111-111110-000002,cmt:
// CN01:Ball
// CN02:Line
// CN03:L-Touch
// CN04:R-Touch
// CN05:C-Touch
// CN06:
// CN07:
// CN08:
// CN09:
// CN10:
//--------------------------------------------------------------------------------
#include "D_Main.h"
#include "D_I2C.h"
#include "D_SIO.h"
#include "D_EIO.h"
//--------------------------------------------------------------------------------
#include "D_Main.h"
#include "D_I2C.h"
#include "D_SIO.h"
#include "D_EIO.h"
//--------------------------------------------------------------------------------
// Program Name : 
//--------------------------------------------------------------------------------
#define GAIN_P 0.09
#define GAIN_I 1
#define GAIN_D 1

#define MOTOR_LIMIT 40
#define PID_LIMIT 25

#define PI 3.14159

//センサー読み取り関数
void Read_Sensors();

//モーター制御系関数
void Move(int Deg, int Power);
void Move_Power(int MotorA, int MotorB, int MotorC, int MotorD);

//姿勢制御系関数
void Calc_PID(void);
void Calc_GoalPID(void);

//ボール追いかけスピード計算
int Calc_MotorSpeed(void);

//最大値、最小値計算
int Max(int a, int b);
int Min(int a, int b);

//ボールセンサ系統変数格納
int IR_Deg;
int IR_Distance;
int before_IR_Deg;  //前回のボールの角度
int before_IR_Distance;   //前回のボールの距離

//カメラ系統変数格納
int Court_Deg;
int Goal_Deg;
int Goal_Distance;

//その他各種センサ変数格納
int Line_Val;
int Gyro_Deg;
int Touch_Val;

//PID制御関連
int Operation_P;
int Operation_I;
int Operation_D;      //各要素ごとの操作量
int deviation;
int deviation_old;   //現在、前回の角度差
int deviation_goal;
int deviation_old_goal;   //現在、前回の角度差
int before_deg;   //前回の角度
int Operation_PID;
int val_P;
int val_I;
int val_D;

BOOL bMove_Line;
//モーターの値を格納
int Motors_Power[4];  //それぞれ1ch~4chを表す
  
//最大値計算
int Max(int a, int b)
{
  return a >= b ? a : b;
}
//最小値計算
int Min(int a, int b)
{
  return a >= b ? b : a;
}
  
//上下限を丸め込む関数
int RemoveHighLow(int value, int High, int Low){
  if(value > High)
    return High;
  else if(value < Low)
    return Low;
    
  return value;
}

void Read_Sensors(){
  //ボールセンサ系統変数格納
  before_IR_Deg = IR_Deg;
  before_IR_Distance = IR_Distance;
  IR_Deg = gAD[CN1];
  IR_Distance = gAD[CN2];

  //カメラ系統変数格納
  Court_Deg = gAD[CN3];
  Goal_Deg = gAD[CN4] - 190;
  Goal_Distance = gAD[CN5];

  //その他各種センサ変数格納
  Line_Val = gAD[CN6];
  Gyro_Deg = gAD[CN7];
  Touch_Val = gAD[CN8];
}

//角度・速度でモーターを動かす
void Move(int Deg, int Power){
  Motors_Power[0] = sin((Deg - 60) * PI / 180) * -Power;
  Motors_Power[1] = sin((Deg + 60) * PI / 180) * Power;
  Motors_Power[2] = sin((Deg - 135) * PI / 180) * -Power;
  Motors_Power[3] = sin((Deg + 135) * PI / 180) * Power;
  Move_Power(Motors_Power[0], Motors_Power[1], Motors_Power[2], Motors_Power[3]);
}

//各モーターの値を代入してモーターを動かす
void Move_Power(int MotorA, int MotorB, int MotorC, int MotorD){
  int Motors[4];
    
  Motors[0] = MotorA + Operation_PID;
  Motors[0] = RemoveHighLow(Motors[0], MOTOR_LIMIT, -MOTOR_LIMIT);
  Motors[1] = MotorB - Operation_PID;
  Motors[1] = RemoveHighLow(Motors[1], MOTOR_LIMIT, -MOTOR_LIMIT);
  Motors[2] = MotorC + Operation_PID;
  Motors[2] = RemoveHighLow(Motors[2], MOTOR_LIMIT, -MOTOR_LIMIT);
  Motors[3] = MotorD - Operation_PID;
  Motors[3] = RemoveHighLow(Motors[3], MOTOR_LIMIT, -MOTOR_LIMIT);

  gPwm[0] = Motors[0] < 0 ? (Motors[0] * -1) | 0x80 : Motors[0];
  gPwm[1] = Motors[1] < 0 ? (Motors[1] * -1) | 0x80 : Motors[1];
  gPwm[2] = Motors[2] < 0 ? (Motors[2] * -1) | 0x80 : Motors[2];
  gPwm[3] = Motors[3] < 0 ? (Motors[3] * -1) | 0x80 : Motors[3];
  pwm_out();
}

//PID制御の計算
void Calc_PID(void){  
  val_P = Gyro_Deg;

  if(val_P > 400){
    val_P = val_P - 800;
  }
  
  val_P = val_P * 2;

  deviation = 0 - Gyro_Deg;
  val_D = deviation - deviation_old;
  deviation_old = deviation;
  
  Operation_P = val_P * GAIN_P;
  Operation_I = 0 * GAIN_I;
  Operation_D = val_D * GAIN_D;
  
  Operation_PID = Operation_P + Operation_I + Operation_D;
  Operation_PID = RemoveHighLow(Operation_PID, PID_LIMIT, -PID_LIMIT);
}

void Calc_GoalPID(void) {
  val_P = Goal_Deg * 1.3;
  if(val_P > 400){
    val_P = val_P - 800;
  }
  deviation_goal = 0 - val_P;
  val_D = deviation_goal - deviation_old_goal;
  deviation_old_goal = deviation_goal;
      
  Operation_PID = val_P * 0.15 + val_D;
  Operation_PID = -RemoveHighLow(Operation_PID, 20, -20);
}

int Calc_MotorSpeed(){
  if(IR_Distance >= 570)
    return 40;
  else if(IR_Distance >= 450)
    return 35;
  
  return 25;
}

void user_main(void)
{  
  while(TRUE){
    Read_Sensors();
    Calc_PID();
    
    if(Line_Val <= 50) {
      if(!bMove_Line) {
        clr_timer(0);
        bMove_Line = true;
      }
    }
        
    if(get_timer(T1) <= 500){
      int move_deg = (Court_Deg - 185) / 700.0 * 360.0;
      int move_speed = 30;
      Move(move_deg, move_speed);
    }
    else 
    {
      bMove_Line = false;
    
      if(IR_Distance <= 520)
      {
        if(IR_Deg <= 800) 
        {
          if(IR_Deg <= 50 || IR_Deg >= 740)
          {
            Move(0, Goal_Distance >= 800 ? 30 : 40);
          } 
          else if(IR_Deg <= 320) 
          {
            int Ball_Deg = Max(IR_Deg / 740.0 * 360.0 + (IR_Deg) / 7.5 + 3, 60); 
            Move(Ball_Deg, (IR_Deg <= 80 && IR_Distance >= 420) ? 25 : 35);
          } 
          else
          {
            int Ball_Deg = Min(IR_Deg / 740.0 * 360.0 - (700 - IR_Deg) / 7.5 - 3, 270);
            Move(Ball_Deg, (IR_Deg >= 640 && IR_Distance >= 420) ? 25 : 35);
          }
        } 
        else 
        {
          Move(0, 0);
        }
      }
      else
      {
      　if(Goal_Distance >= 600)
      　{
          if(Goal_Distance >= 800)
          {
             Move(180, 40);
          }
          else
          {
            int goal_deg = Goal_Deg / (780.0 - 190.0) * 360.0;
            Move(goal_deg, 20 + (Goal_Distance - 600) / 10);
          }
        }
        else
        {
          if(Goal_Distance <= 510)
          {
            Move(0, 20);
          }
          else
          {
            if(Goal_Deg <= 440 - 190)
            {
              Move(90, 30);
            }
            else if(Goal_Deg >= 470 - 190)
            {
              Move(270, 30);
            }
            else
            {
              Move(0, 0);
            }
          }
        }
      }
    }
  }
}
