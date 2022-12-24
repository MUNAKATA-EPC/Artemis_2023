#include "D_Main.h"
#include "D_I2C.h"
#include "D_SIO.h"
#include "D_EIO.h"
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

#define MOTOR_LIMIT 40
#define PID_LIMIT 25

#define PI 3.14159

//�Z���T�[�ǂݎ��֐�
void Read_Sensors();

//���[�^�[����n�֐�
void Move(int Deg, int Power);
void Move_Power(int MotorA, int MotorB, int MotorC, int MotorD);

//�p������n�֐�
void Calc_PID(void);
void Calc_GoalPID(void);

//�{�[���ǂ������X�s�[�h�v�Z
int Calc_MotorSpeed(void);

//�{�[���Z���T�n���ϐ��i�[
int IR_Deg;
int IR_Distance;
int before_IR_Deg;  //�O��̃{�[���̊p�x
int before_IR_Distance;   //�O��̃{�[���̋���

//�J�����n���ϐ��i�[
int Court_Deg;
int Goal_Deg;
int Goal_Distance;

//���̑��e��Z���T�ϐ��i�[
int Line_Val;
int Gyro_Deg;
int Touch_Val;

//PID����֘A
int Operation_P;
int Operation_I;
int Operation_D;      //�e�v�f���Ƃ̑����
int deviation;
int deviation_old;   //���݁A�O��̊p�x��
int deviation_goal;
int deviation_old_goal;   //���݁A�O��̊p�x��
int before_deg;   //�O��̊p�x
int Operation_PID;
int val_P;
int val_I;
int val_D;

BOOL bMove_Line;
//���[�^�[�̒l���i�[
int Motors_Power[4];  //���ꂼ��1ch~4ch��\��
  
//�㉺�����ۂߍ��ފ֐�
int RemoveHighLow(int value, int High, int Low){
  if(value > High)
    return High;
  else if(value < Low)
    return Low;
    
  return value;
}

void Read_Sensors(){
  //�{�[���Z���T�n���ϐ��i�[
  before_IR_Deg = IR_Deg;
  before_IR_Distance = IR_Distance;
  IR_Deg = gAD[CN1];
  IR_Distance = gAD[CN2];

  //�J�����n���ϐ��i�[
  Court_Deg = gAD[CN3];
  Goal_Deg = gAD[CN4];
  Goal_Distance = gAD[CN5];

  //���̑��e��Z���T�ϐ��i�[
  Line_Val = gAD[CN6];
  Gyro_Deg = gAD[CN7];
  Touch_Val = gAD[CN8];
}

//�p�x�E���x�Ń��[�^�[�𓮂���
void Move(int Deg, int Power){
  Motors_Power[0] = sin((Deg - 60) * PI / 180) * -Power;
  Motors_Power[1] = sin((Deg + 60) * PI / 180) * Power;
  Motors_Power[2] = sin((Deg - 135) * PI / 180) * -Power;
  Motors_Power[3] = sin((Deg + 135) * PI / 180) * Power;
  Move_Power(Motors_Power[0], Motors_Power[1], Motors_Power[2], Motors_Power[3]);
}

//�e���[�^�[�̒l�������ă��[�^�[�𓮂���
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

//PID����̌v�Z
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
    
    if(IR_Deg <= 800) 
    {
      if(IR_Deg <= 73 || IR_Deg >= 720)
      {
         Move(0, 30);
      } 
      else if(IR_Deg <= 320) 
      {
        int Ball_Deg = IR_Deg / 740.0 * 360.0 + 10; 
        Move(Ball_Deg, 30);
      } 
      else
      {
         int Ball_Deg = IR_Deg / 740.0 * 360.0 - 10;
         Move(Ball_Deg, 30);
      }
    } 
    else 
    {
      Move(0, 0);
    }
  }
}


