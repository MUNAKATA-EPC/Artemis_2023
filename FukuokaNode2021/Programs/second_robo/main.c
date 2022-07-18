//--------------------------------------------------------------------------------
// Title: Main - [ main ]
// Build:DAISEN C-Style for TJ3B  [ Ver.20190706 ] - [ Build_V190617 ]
//--------------------------------------------------------------------------------
// SetupVal:111111-113310-002002,cmt:
// CN01:Ball
// CN02:Line
// CN03:L-Touch
// CN04:R-Touch
// CN05:C-Touch
// CN06:
// CN07:
// CN08:
// CN09:PING
// CN10:PING
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
// Program Name : pid.C
//--------------------------------------------------------------------------------
void user_sub_1(void)
{
  gV[VAR_A] = get_bno(0);
  set_Led(1, LED_OFF);
  if (gV[VAR_A] > 180) {
    set_Led(1, LED_ON);
    gV[VAR_A] = gV[VAR_A] - 360;
  }
  gV[VAR_D] = gV[VAR_A] * gV[VAR_S];
  gV[VAR_F] = gV[VAR_D] + gV[VAR_E];
  if (gV[VAR_F] > gV[VAR_M]) {
    gV[VAR_F] = gV[VAR_M];
  } else if (gV[VAR_F] < gV[VAR_M] * -1) {
    gV[VAR_F] = gV[VAR_M] * -1;
  }
  gV[VAR_H] = gV[VAR_F] + gV[VAR_W];
  gV[VAR_I] = gV[VAR_F] + gV[VAR_X];
  gV[VAR_J] = gV[VAR_F] + gV[VAR_Y];
  gV[VAR_K] = gV[VAR_F] + gV[VAR_Z];
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
// Program Name : main.C
//--------------------------------------------------------------------------------
void user_main(void)
{
  gV[VAR_M] = 60;
  gV[VAR_S] = 1;
  gV[VAR_T] = 10;
  while (TRUE) {
    user_sub_1();
    user_sub_2();
  }
}
//--------------------------------------------------------------------------------
