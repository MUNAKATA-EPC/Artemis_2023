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
void user_sub_1(void);
void user_sub_2(void);
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
// Program Name : front60.C
//--------------------------------------------------------------------------------
void user_sub_2(void)
{
  gV[VAR_W] = 60;
  gV[VAR_X] = 60;
  gV[VAR_Y] = 60;
  gV[VAR_Z] = 60;
  gPwm[0] = gV[VAR_H] < 0 ? (gV[VAR_H] * -1) | 0x80 : gV[VAR_H];
  gPwm[1] = gV[VAR_I] < 0 ? (gV[VAR_I] * -1) | 0x80 : gV[VAR_I];
  gPwm[2] = gV[VAR_J] < 0 ? (gV[VAR_J] * -1) | 0x80 : gV[VAR_J];
  gPwm[3] = gV[VAR_K] < 0 ? (gV[VAR_K] * -1) | 0x80 : gV[VAR_K];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : main.C
//--------------------------------------------------------------------------------
void user_main(void)
{
  gV[VAR_L] = 0;
  clr_timer(0);
  while (TRUE) {
    if (get_timer(T1) > 1000L) {
      user_sub_1();
      if (gAD[CN6] < 102) {
        gV[VAR_L] = 1;
      }
      if (gV[VAR_L] == 0) {
        user_sub_2();
      } else {
        gPwm[0] = 0x00;
        gPwm[1] = 0x00;
        gPwm[2] = 0x00;
        gPwm[3] = 0x00;
        pwm_out();
      }
    } else {
      gPwm[0] = 0x00;
      gPwm[1] = 0x00;
      gPwm[2] = 0x00;
      gPwm[3] = 0x00;
      pwm_out();
    }
  }
}
//--------------------------------------------------------------------------------
