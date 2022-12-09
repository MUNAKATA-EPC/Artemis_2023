//--------------------------------------------------------------------------------
#include "D_Main.h"
#include "D_I2C.h"
#include "D_SIO.h"
#include "D_EIO.h"
//--------------------------------------------------------------------------------
// Functions
//--------------------------------------------------------------------------------
void user_sub_1(void);
void user_sub_2(void);
void user_sub_6(void);
void user_sub_5(void);
void user_sub_3(void);
void user_sub_4(void);
void user_main(void);
//--------------------------------------------------------------------------------
// Program Name : pid-modoki.C
//--------------------------------------------------------------------------------
void user_sub_1(void)
{
  gV[VAR_A] = gAD[CN7];
  if (gV[VAR_A] > 400) {
    gV[VAR_A] = gV[VAR_A] - 800;
  }
  gV[VAR_A] = gV[VAR_A] / 4;
  if (gV[VAR_A] > 25) {
    gV[VAR_A] = 25;
  } else if (gV[VAR_A] < - 25) {
    gV[VAR_A] = - 25;
  }
  gV[VAR_H] = gV[VAR_W] + gV[VAR_A];
  gV[VAR_I] = gV[VAR_X] - gV[VAR_A];
  gV[VAR_J] = gV[VAR_Y] + gV[VAR_A];
  gV[VAR_K] = gV[VAR_Z] - gV[VAR_A];
}
//--------------------------------------------------------------------------------
// Program Name : back.C
//--------------------------------------------------------------------------------
void user_sub_2(void)
{
  gV[VAR_W] = - 35;
  gV[VAR_X] = - 35;
  gV[VAR_Y] = - 35;
  gV[VAR_Z] = - 35;
  gPwm[0] = gV[VAR_H] < 0 ? (gV[VAR_H] * -1) | 0x80 : gV[VAR_H];
  gPwm[1] = gV[VAR_I] < 0 ? (gV[VAR_I] * -1) | 0x80 : gV[VAR_I];
  gPwm[2] = gV[VAR_J] < 0 ? (gV[VAR_J] * -1) | 0x80 : gV[VAR_J];
  gPwm[3] = gV[VAR_K] < 0 ? (gV[VAR_K] * -1) | 0x80 : gV[VAR_K];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : back_slow.C
//--------------------------------------------------------------------------------
void user_sub_6(void)
{
  gV[VAR_W] = - 25;
  gV[VAR_X] = - 25;
  gV[VAR_Y] = - 25;
  gV[VAR_Z] = - 25;
  gPwm[0] = gV[VAR_H] < 0 ? (gV[VAR_H] * -1) | 0x80 : gV[VAR_H];
  gPwm[1] = gV[VAR_I] < 0 ? (gV[VAR_I] * -1) | 0x80 : gV[VAR_I];
  gPwm[2] = gV[VAR_J] < 0 ? (gV[VAR_J] * -1) | 0x80 : gV[VAR_J];
  gPwm[3] = gV[VAR_K] < 0 ? (gV[VAR_K] * -1) | 0x80 : gV[VAR_K];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : stop.C
//--------------------------------------------------------------------------------
void user_sub_5(void)
{
  gV[VAR_W] = 0;
  gV[VAR_X] = 0;
  gV[VAR_Y] = 0;
  gV[VAR_Z] = 0;
  gPwm[0] = gV[VAR_H] < 0 ? (gV[VAR_H] * -1) | 0x80 : gV[VAR_H];
  gPwm[1] = gV[VAR_I] < 0 ? (gV[VAR_I] * -1) | 0x80 : gV[VAR_I];
  gPwm[2] = gV[VAR_J] < 0 ? (gV[VAR_J] * -1) | 0x80 : gV[VAR_J];
  gPwm[3] = gV[VAR_K] < 0 ? (gV[VAR_K] * -1) | 0x80 : gV[VAR_K];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : rightback.C
//--------------------------------------------------------------------------------
void user_sub_3(void)
{
  gV[VAR_W] = - 35;
  gV[VAR_X] = 0;
  gV[VAR_Y] = 0;
  gV[VAR_Z] = - 35;
  gPwm[0] = gV[VAR_H] < 0 ? (gV[VAR_H] * -1) | 0x80 : gV[VAR_H];
  gPwm[1] = gV[VAR_I] < 0 ? (gV[VAR_I] * -1) | 0x80 : gV[VAR_I];
  gPwm[2] = gV[VAR_J] < 0 ? (gV[VAR_J] * -1) | 0x80 : gV[VAR_J];
  gPwm[3] = gV[VAR_K] < 0 ? (gV[VAR_K] * -1) | 0x80 : gV[VAR_K];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : leftback.C
//--------------------------------------------------------------------------------
void user_sub_4(void)
{
  gV[VAR_W] = 0;
  gV[VAR_X] = - 35;
  gV[VAR_Y] = - 35;
  gV[VAR_Z] = 0;
  gPwm[0] = gV[VAR_H] < 0 ? (gV[VAR_H] * -1) | 0x80 : gV[VAR_H];
  gPwm[1] = gV[VAR_I] < 0 ? (gV[VAR_I] * -1) | 0x80 : gV[VAR_I];
  gPwm[2] = gV[VAR_J] < 0 ? (gV[VAR_J] * -1) | 0x80 : gV[VAR_J];
  gPwm[3] = gV[VAR_K] < 0 ? (gV[VAR_K] * -1) | 0x80 : gV[VAR_K];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : main_second.C
//--------------------------------------------------------------------------------
void user_main(void)
{
  while (TRUE) {
    user_sub_1();
    if (gAD[CN4] > 501) {
      if (gAD[CN4] < 531) {
        if (gAD[CN5] < 562) {
          if (gAD[CN5] < 480) {
            user_sub_2();
          } else {
            user_sub_6();
          }
        } else {
          user_sub_5();
        }
      } else {
        user_sub_3();
      }
    } else {
      if (gAD[CN4] < 460) {
        user_sub_4();
      } else {
        if (gAD[CN5] < 562) {
          if (gAD[CN5] < 480) {
            user_sub_2();
          } else {
            user_sub_6();
          }
        } else {
          user_sub_5();
        }
      }
    }
  }
}
//--------------------------------------------------------------------------------
