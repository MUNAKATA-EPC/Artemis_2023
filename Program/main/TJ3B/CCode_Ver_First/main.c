//--------------------------------------------------------------------------------
// Title: Main - [ main.c ]
// Build:DAISEN C-Style for TJ3B  [ Ver.20190706 ] - [ Build_V190617 ]
//--------------------------------------------------------------------------------
// SetupVal:111111-111110-000002,cmt:
// CN01:Ball
// CN02:Line
// CN03:L-Touch
// CN04:R-Touch
// CN05:
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

#define GAIN_P 0.15
#define GAIN_I 1
#define GAIN_D 1

#define MOTOR_LIMIT 35
#define PID_LIMIT 20

#define IR_MAX 576.0

#define PI 3.14159

//�Z���T�[�ǂݎ��֐�
void Read_Sensors();

//���[�^�[����n�֐�
void Move(int Deg, int Power);
void Move_Power(int MotorA, int MotorB, int MotorC, int MotorD);

//�p������n�֐�
void Calc_PID(BOOL bDecide);
void Calc_GoalPID(BOOL bDecide);

//�{�[���ǂ������X�s�[�h�v�Z
int Calc_MotorSpeed(void);

//�{�[���Z���T�n���ϐ��i�[
int IR_Deg;
int IR_Distance;

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
int Operation_PID;
int val_P;
int val_I;
int val_D;

int PID_Type;

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
  IR_Deg = gAD[CN1];
  IR_Distance = gAD[CN2];

  //�J�����n���ϐ��i�[
  Court_Deg = gAD[CN3];
        Goal_Deg = gAD[CN4] - 190;
  Goal_Distance = gAD[CN5];

  //���̑��e��Z���T�ϐ��i�[
  Line_Val = gAD[CN6];
  Gyro_Deg = gAD[CN7];
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

//PID����̌v�Z
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
  deviation_goal = 0 - val_P;
  val_D = deviation_goal - deviation_old_goal;
  deviation_old_goal = deviation_goal;
        
  if(bDecide) {
          Operation_PID = val_P * 0.1 + val_D;
    Operation_PID = -RemoveHighLow(Operation_PID, 20, -20);
  }
}

int Calc_MotorSpeed(){
  if(IR_Deg <= 150 || IR_Deg >= 650)
        return 35;
  else {
    if(IR_Distance >= 570)
       return 45;
    else if(IR_Distance >= 450)
       return 40;
    }                
    
  return 35;
}

void user_main(void)
{
  while(TRUE){
    int move_deg;
    int move_speed;
        
    Read_Sensors();
            if(Goal_Deg <= 800)
      Calc_GoalPID(true);
    else
      Calc_PID(true);
    
    //���C���Z���T����
            if(Line_Val <= 50) {
      if(!bMove_Line) {
        clr_timer(0);
        bMove_Line = true;
      }
    }
    
    if(get_timer(T1) <= 400){
      move_deg = (Court_Deg - 185) / 700.0 * 360.0;
      move_speed = 35;
      Move(move_deg, move_speed);
    }
    else {
      bMove_Line = false;
          
      if(IR_Deg < 800) { //�������Ă��邩�ۂ�
          if(IR_Deg < 55 || IR_Deg > 700) {
            Move(0, 45);
          }
          else if(IR_Deg < 420) {
            int adddeg = 35 + PID_Type * 5 + (IR_Distance <= 440 ? 5 : 0);                         
            move_deg = (IR_Deg / 740.0 * 360.0) + adddeg;
            Move(move_deg, Calc_MotorSpeed());
          }
          else{
                      int adddeg = 40 + PID_Type * 3;
            move_deg = (IR_Deg / 740.0 * 360.0) - adddeg;
            Move(move_deg, Calc_MotorSpeed());
          }
      }
      else {
        Move(0, 0);
      }
    }
  }
}
