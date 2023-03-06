//--------------------------------------------------------------------------------
// Title: Main - [ NewFile-00 ]
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
// Program Name : 
//--------------------------------------------------------------------------------
#define GAIN_P 0.15
#define GAIN_I 1
#define GAIN_D 1

#define MOTOR_LIMIT 35
#define PID_LIMIT 20

#define IR_MAX 576.0

#define PI 3.14159

//センサー読み取り関数
void Read_Sensors();

//モーター制御系関数
void Move(int Deg, int Power);
void Move_Power(int MotorA, int MotorB, int MotorC, int MotorD);

//姿勢制御系関数
void Calc_PID(BOOL bDecide);
void Calc_GoalPID(BOOL bDecide);

//ボール追いかけスピード計算
int Calc_MotorSpeed(void);

//max
int max(int a, int b);

//ボールセンサ系統変数格納
int IR_Deg;
int IR_Distance;

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
int Operation_PID;
int val_P;
int val_I;
int val_D;

int PID_Type;

BOOL bMove_Line;

//モーターの値を格納
int Motors_Power[4];  //それぞれ1ch~4chを表す
  
int max(int a, int b)
{
  return a >= b ? a : b;
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
  IR_Deg = gAD[CN1];
  IR_Distance = gAD[CN2];

  //カメラ系統変数格納
  Court_Deg = gAD[CN3];
  Goal_Deg = gAD[CN4] - 170;
  Goal_Distance = gAD[CN5];

  //その他各種センサ変数格納
  Line_Val = gAD[CN6];
  Gyro_Deg = gAD[CN7];
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
  Motors[1] = RemoveHighLow(Motors[0], MOTOR_LIMIT, -MOTOR_LIMIT);
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
void Calc_PID(BOOL bDecide){
  PID_Type = 0;
  val_P = Gyro_Deg;

  if(val_P > 400){
    val_P = val_P - 800;
  }
  
  val_P = val_P * 2;

  deviation = 0 - Gyro_Deg;
  val_D = deviation - deviation_old;
  deviation_old = deviation;
  
  if(bDecide) {
    Operation_P = val_P * GAIN_P;
    Operation_I = 0 * GAIN_I;
    Operation_D = val_D * GAIN_D;
  
    Operation_PID = Operation_P + Operation_I + Operation_D;
    Operation_PID = RemoveHighLow(Operation_PID, PID_LIMIT, -PID_LIMIT);
  }
}

void Calc_GoalPID(BOOL bDecide) {
  PID_Type = 1;
  val_P = Goal_Deg * 1.3;
  if(val_P > 400){
    val_P = val_P - 800;
  }
  deviation = 0 - val_P;
  val_D = deviation - deviation_old;
  deviation_old = deviation;
        
  if(bDecide) {
    Operation_PID = val_P * 0.09 + val_D;
    Operation_PID = -RemoveHighLow(Operation_PID, 20, -20);
  }
}

int Calc_MotorSpeed(){ 
  if(IR_Deg <= 140 || IR_Deg >= 650)
    return 33;

  return 40;
}

void user_main(void)
{
  while(TRUE){
    int move_deg;
    int move_speed;
        
    Read_Sensors();
    
    Calc_PID(true);
      
    //ラインセンサ処理
    if(Line_Val <= 50) {
      if(!bMove_Line) {
        clr_timer(0);
        bMove_Line = true;
      }
    }
    
    if(get_timer(T1) <= 500){
      move_deg = ((Court_Deg - 185) / 700.0 * 360.0 + 22) / 45 * 45;
      move_speed = 30;
      Move(move_deg, move_speed);
    }
    else {
      
    }
  }
}

