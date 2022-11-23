//--------------------------------------------------------------------------------
// Title: Main - [ NewFile-00 ]
// Build:DAISEN C-Style for TJ3B  [ Ver.20190706 ] - [ Build_V190617 ]
//--------------------------------------------------------------------------------
// SetupVal:111111-110010-000002,cmt:
// CN01:Ball
// CN02:Line
// CN03:L-Touch
// CN04:R-Touch
// CN05:C-Touch
// CN06:
// CN07:
// CN08:
// CN09:RED3
// CN10:RED2
//--------------------------------------------------------------------------------
#include "D_Main.h"
#include "D_I2C.h"
#include "D_SIO.h"
#include "D_EIO.h"
//--------------------------------------------------------------------------------
// Functions
//--------------------------------------------------------------------------------
void user_sub_3(void);
void user_sub_1(void);
void user_sub_2(void);
void user_main(void);
//--------------------------------------------------------------------------------
// Program Name : pid-modoki.C
//--------------------------------------------------------------------------------
void user_sub_3(void)
{
  gV[VAR_A] = gAD[CN7];
  if (gV[VAR_A] > 360) {
    gV[VAR_A] = gV[VAR_A] - 720;
  }
  gV[VAR_A] = gV[VAR_A] / 3;
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
// Program Name : leftfront.C
//--------------------------------------------------------------------------------
void user_sub_1(void)
{
  gV[VAR_W] = 30;
  gV[VAR_X] = 15;
  gV[VAR_Y] = 15;
  gV[VAR_Z] = 30;
  gPwm[0] = gV[VAR_H] < 0 ? (gV[VAR_H] * -1) | 0x80 : gV[VAR_H];
  gPwm[1] = gV[VAR_I] < 0 ? (gV[VAR_I] * -1) | 0x80 : gV[VAR_I];
  gPwm[2] = gV[VAR_J] < 0 ? (gV[VAR_J] * -1) | 0x80 : gV[VAR_J];
  gPwm[3] = gV[VAR_K] < 0 ? (gV[VAR_K] * -1) | 0x80 : gV[VAR_K];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : stop.C
//--------------------------------------------------------------------------------
void user_sub_2(void)
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
// Program Name : NewFile-00.C
//--------------------------------------------------------------------------------
void user_main(void)
{
  while (TRUE) {
    user_sub_3();
    if (gAD[CN8] > 102) {
      user_sub_1();
    } else {
      user_sub_2();
    }
  }
}
//--------------------------------------------------------------------------------
