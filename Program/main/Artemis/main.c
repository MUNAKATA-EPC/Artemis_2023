//--------------------------------------------------------------------------------
// Title: Main - [ main ]
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
// Functions
//--------------------------------------------------------------------------------
void user_sub_7(void);
void user_sub_3(void);
void user_sub_1(void);
void user_sub_2(void);
void user_sub_4(void);
void user_sub_5(void);
void user_sub_6(void);
void user_main(void);
//--------------------------------------------------------------------------------
// Program Name : pid_modoki.C
//--------------------------------------------------------------------------------
void user_sub_7(void)
{
  gV[VAR_A] = gAD[CN1];
  gV[VAR_M] = 30;
  if (gV[VAR_A] > 35) {
    gV[VAR_A] = gV[VAR_A] - 70;
  }
  gV[VAR_C] = gV[VAR_A] - gV[VAR_B];
  gV[VAR_B] = gV[VAR_A];
  gV[VAR_D] = gV[VAR_A] * gV[VAR_S];
  gV[VAR_E] = gV[VAR_C] * gV[VAR_T];
  gV[VAR_F] = gV[VAR_D] + gV[VAR_E];
  if (gV[VAR_F] > gV[VAR_M]) {
    gV[VAR_F] = gV[VAR_M];
  } else if (gV[VAR_F] < gV[VAR_M] * -1) {
    gV[VAR_F] = gV[VAR_M] * -1;
  }
  gV[VAR_H] = gV[VAR_W] + gV[VAR_F];
  gV[VAR_I] = gV[VAR_X] - gV[VAR_F];
  gV[VAR_J] = gV[VAR_Y] + gV[VAR_F];
  gV[VAR_K] = gV[VAR_Z] - gV[VAR_F];
  if (gV[VAR_H] > gV[VAR_M]) {
    gV[VAR_H] = gV[VAR_M];
  } else if (gV[VAR_H] < gV[VAR_M] * -1) {
    gV[VAR_H] = gV[VAR_M] * -1;
  }
  if (gV[VAR_I] > gV[VAR_M]) {
    gV[VAR_I] = gV[VAR_M];
  } else if (gV[VAR_I] < gV[VAR_M] * -1) {
    gV[VAR_I] = gV[VAR_M] * -1;
  }
  if (gV[VAR_J] > gV[VAR_M]) {
    gV[VAR_J] = gV[VAR_M];
  } else if (gV[VAR_J] < gV[VAR_M] * -1) {
    gV[VAR_J] = gV[VAR_M] * -1;
  }
  if (gV[VAR_K] > gV[VAR_M]) {
    gV[VAR_K] = gV[VAR_M];
  } else if (gV[VAR_K] < gV[VAR_M] * -1) {
    gV[VAR_K] = gV[VAR_M] * -1;
  }
}
//--------------------------------------------------------------------------------
// Program Name : stop.C
//--------------------------------------------------------------------------------
void user_sub_3(void)
{
  gV[VAR_H] = 0;
  gV[VAR_I] = 0;
  gV[VAR_J] = 0;
  gV[VAR_K] = 0;
  gPwm[0] = gV[VAR_W] < 0 ? (gV[VAR_W] * -1) | 0x80 : gV[VAR_W];
  gPwm[1] = gV[VAR_X] < 0 ? (gV[VAR_X] * -1) | 0x80 : gV[VAR_X];
  gPwm[2] = gV[VAR_Y] < 0 ? (gV[VAR_Y] * -1) | 0x80 : gV[VAR_Y];
  gPwm[3] = gV[VAR_Z] < 0 ? (gV[VAR_Z] * -1) | 0x80 : gV[VAR_Z];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : front.C
//--------------------------------------------------------------------------------
void user_sub_1(void)
{
  gV[VAR_H] = 30;
  gV[VAR_I] = 30;
  gV[VAR_J] = 30;
  gV[VAR_K] = 30;
  gPwm[0] = gV[VAR_W] < 0 ? (gV[VAR_W] * -1) | 0x80 : gV[VAR_W];
  gPwm[1] = gV[VAR_X] < 0 ? (gV[VAR_X] * -1) | 0x80 : gV[VAR_X];
  gPwm[2] = gV[VAR_Y] < 0 ? (gV[VAR_Y] * -1) | 0x80 : gV[VAR_Y];
  gPwm[3] = gV[VAR_Z] < 0 ? (gV[VAR_Z] * -1) | 0x80 : gV[VAR_Z];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : right.C
//--------------------------------------------------------------------------------
void user_sub_2(void)
{
  gV[VAR_H] = 30;
  gV[VAR_I] = - 30;
  gV[VAR_J] = - 30;
  gV[VAR_K] = 30;
  gPwm[0] = gV[VAR_W] < 0 ? (gV[VAR_W] * -1) | 0x80 : gV[VAR_W];
  gPwm[1] = gV[VAR_X] < 0 ? (gV[VAR_X] * -1) | 0x80 : gV[VAR_X];
  gPwm[2] = gV[VAR_Y] < 0 ? (gV[VAR_Y] * -1) | 0x80 : gV[VAR_Y];
  gPwm[3] = gV[VAR_Z] < 0 ? (gV[VAR_Z] * -1) | 0x80 : gV[VAR_Z];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : back.C
//--------------------------------------------------------------------------------
void user_sub_4(void)
{
  gV[VAR_H] = - 30;
  gV[VAR_I] = - 30;
  gV[VAR_J] = - 30;
  gV[VAR_K] = - 30;
  gPwm[0] = gV[VAR_W] < 0 ? (gV[VAR_W] * -1) | 0x80 : gV[VAR_W];
  gPwm[1] = gV[VAR_X] < 0 ? (gV[VAR_X] * -1) | 0x80 : gV[VAR_X];
  gPwm[2] = gV[VAR_Y] < 0 ? (gV[VAR_Y] * -1) | 0x80 : gV[VAR_Y];
  gPwm[3] = gV[VAR_Z] < 0 ? (gV[VAR_Z] * -1) | 0x80 : gV[VAR_Z];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : rightfront.C
//--------------------------------------------------------------------------------
void user_sub_5(void)
{
  gV[VAR_H] = 30;
  gV[VAR_I] = 0;
  gV[VAR_J] = 0;
  gV[VAR_K] = 30;
  gPwm[0] = gV[VAR_W] < 0 ? (gV[VAR_W] * -1) | 0x80 : gV[VAR_W];
  gPwm[1] = gV[VAR_X] < 0 ? (gV[VAR_X] * -1) | 0x80 : gV[VAR_X];
  gPwm[2] = gV[VAR_Y] < 0 ? (gV[VAR_Y] * -1) | 0x80 : gV[VAR_Y];
  gPwm[3] = gV[VAR_Z] < 0 ? (gV[VAR_Z] * -1) | 0x80 : gV[VAR_Z];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : left.C
//--------------------------------------------------------------------------------
void user_sub_6(void)
{
  gV[VAR_H] = - 30;
  gV[VAR_I] = 30;
  gV[VAR_J] = 30;
  gV[VAR_K] = - 30;
  gPwm[0] = gV[VAR_W] < 0 ? (gV[VAR_W] * -1) | 0x80 : gV[VAR_W];
  gPwm[1] = gV[VAR_X] < 0 ? (gV[VAR_X] * -1) | 0x80 : gV[VAR_X];
  gPwm[2] = gV[VAR_Y] < 0 ? (gV[VAR_Y] * -1) | 0x80 : gV[VAR_Y];
  gPwm[3] = gV[VAR_Z] < 0 ? (gV[VAR_Z] * -1) | 0x80 : gV[VAR_Z];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : main.C
//--------------------------------------------------------------------------------
void user_main(void)
{
  gV[VAR_S] = 1;  	// ”ä—áƒQƒCƒ“
  gV[VAR_T] = 6;  	// ”÷•ªƒQƒCƒ“
  while (TRUE) {
    user_sub_7();
    if (gAD[CN6] < 306) {
      user_sub_3();
    } else {
      if (gAD[CN1] < 61) {
        user_sub_1();
      } else if (gAD[CN1] < 102) {
        user_sub_2();
      } else if (gAD[CN1] < 143) {
        user_sub_3();
      } else if (gAD[CN1] < 184) {
        user_sub_4();
      } else if (gAD[CN1] < 225) {
        user_sub_4();
      } else if (gAD[CN1] < 265) {
        user_sub_5();
      } else if (gAD[CN1] < 306) {
        user_sub_5();
      } else if (gAD[CN1] < 347) {
        user_sub_5();
      } else if (gAD[CN1] < 388) {
        user_sub_3();
      } else if (gAD[CN1] < 429) {
        user_sub_3();
      } else if (gAD[CN1] < 470) {
        user_sub_3();
      } else if (gAD[CN1] < 511) {
        user_sub_4();
      } else if (gAD[CN1] < 552) {
        user_sub_4();
      } else if (gAD[CN1] < 593) {
        user_sub_5();
      } else if (gAD[CN1] < 634) {
        user_sub_6();
      } else if (gAD[CN1] < 675) {
        user_sub_1();
      } else {
        user_sub_3();
      }
    }
  }
}
//--------------------------------------------------------------------------------
