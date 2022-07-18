//--------------------------------------------------------------------------------
// Title: Main - [ main ]
// Build:DAISEN C-Style for TJ3B  [ Ver.20190706 ] - [ Build_V190617 ]
//--------------------------------------------------------------------------------
// SetupVal:111111-333310-002002,cmt:
// CN01:IR_FLeft
// CN02:IR_FRIght
// CN03:IR_Left
// CN04:IR_Right
// CN05:Line
// CN06:IR_Front
// CN07:Front
// CN08:Right
// CN09:Left
// CN10:Back
//--------------------------------------------------------------------------------
#include "D_Main.h"
#include "D_I2C.h"
#include "D_SIO.h"
#include "D_EIO.h"
//--------------------------------------------------------------------------------
// Functions
//--------------------------------------------------------------------------------
void user_sub_1(void);
void user_sub_8(void);
void user_sub_5(void);
void user_sub_7(void);
void user_sub_2(void);
void user_sub_3(void);
void user_sub_4(void);
void user_main(void);
//--------------------------------------------------------------------------------
// Program Name : pid_modoki.C
//--------------------------------------------------------------------------------
void user_sub_1(void)
{
  gV[VAR_A] = get_bno(0);
  gV[VAR_M] = 80;
  if (gV[VAR_A] > 180) {
    gV[VAR_A] = gV[VAR_A] - 360;
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
}
//--------------------------------------------------------------------------------
// Program Name : stop.C
//--------------------------------------------------------------------------------
void user_sub_8(void)
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
// Program Name : back.C
//--------------------------------------------------------------------------------
void user_sub_5(void)
{
  gV[VAR_W] = 53;
  gV[VAR_X] = 55;
  gV[VAR_Y] = 50;
  gV[VAR_Z] = 63;
  gPwm[0] = gV[VAR_H] < 0 ? (gV[VAR_H] * -1) | 0x80 : gV[VAR_H];
  gPwm[1] = gV[VAR_I] < 0 ? (gV[VAR_I] * -1) | 0x80 : gV[VAR_I];
  gPwm[2] = gV[VAR_J] < 0 ? (gV[VAR_J] * -1) | 0x80 : gV[VAR_J];
  gPwm[3] = gV[VAR_K] < 0 ? (gV[VAR_K] * -1) | 0x80 : gV[VAR_K];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : front.C
//--------------------------------------------------------------------------------
void user_sub_7(void)
{
  gV[VAR_W] = - 53;
  gV[VAR_X] = - 55;
  gV[VAR_Y] = - 50;
  gV[VAR_Z] = - 63;
  gPwm[0] = gV[VAR_H] < 0 ? (gV[VAR_H] * -1) | 0x80 : gV[VAR_H];
  gPwm[1] = gV[VAR_I] < 0 ? (gV[VAR_I] * -1) | 0x80 : gV[VAR_I];
  gPwm[2] = gV[VAR_J] < 0 ? (gV[VAR_J] * -1) | 0x80 : gV[VAR_J];
  gPwm[3] = gV[VAR_K] < 0 ? (gV[VAR_K] * -1) | 0x80 : gV[VAR_K];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : left.C
//--------------------------------------------------------------------------------
void user_sub_2(void)
{
  gV[VAR_W] = 40;
  gV[VAR_X] = - 55;
  gV[VAR_Y] = - 50;
  gV[VAR_Z] = 50;
  gPwm[0] = gV[VAR_H] < 0 ? (gV[VAR_H] * -1) | 0x80 : gV[VAR_H];
  gPwm[1] = gV[VAR_I] < 0 ? (gV[VAR_I] * -1) | 0x80 : gV[VAR_I];
  gPwm[2] = gV[VAR_J] < 0 ? (gV[VAR_J] * -1) | 0x80 : gV[VAR_J];
  gPwm[3] = gV[VAR_K] < 0 ? (gV[VAR_K] * -1) | 0x80 : gV[VAR_K];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : right.C
//--------------------------------------------------------------------------------
void user_sub_3(void)
{
  gV[VAR_W] = - 40;
  gV[VAR_X] = 55;
  gV[VAR_Y] = 50;
  gV[VAR_Z] = - 50;
  gPwm[0] = gV[VAR_H] < 0 ? (gV[VAR_H] * -1) | 0x80 : gV[VAR_H];
  gPwm[1] = gV[VAR_I] < 0 ? (gV[VAR_I] * -1) | 0x80 : gV[VAR_I];
  gPwm[2] = gV[VAR_J] < 0 ? (gV[VAR_J] * -1) | 0x80 : gV[VAR_J];
  gPwm[3] = gV[VAR_K] < 0 ? (gV[VAR_K] * -1) | 0x80 : gV[VAR_K];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : BLeft.C
//--------------------------------------------------------------------------------
void user_sub_4(void)
{
  gV[VAR_W] = 40;
  gV[VAR_X] = 0;
  gV[VAR_Y] = 0;
  gV[VAR_Z] = 50;
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
  gV[VAR_S] = 1;  	// ”ä—áƒQƒCƒ“
  gV[VAR_T] = 10;  	// ”÷•ªƒQƒCƒ“
  while (TRUE) {
    user_sub_1();
    if (gAD[CN5] < 102) {
      if (gV[VAR_L] == 0) {
        clr_timer(0);
        gV[VAR_L] = 1;
      }
    }
    if (get_timer(T1) < 100L) {
      gPwm[0] = 0x00 | 0x80;
      gPwm[1] = 0x00 | 0x80;
      gPwm[2] = 0x00 | 0x80;
      gPwm[3] = 0x00 | 0x80;
      pwm_out();
    } else if (get_timer(T1) < 400L) {
      user_sub_8();
    } else if (get_timer(T1) < 1000L) {
      if (get_ping(CN8) < 300) {
        if (get_ping(CN7) < 300) {
          user_sub_5();
        } else if (get_ping(CN10) < 300) {
          user_sub_7();
        } else {
          user_sub_2();
        }
      } else if (get_ping(CN9) < 300) {
        if (get_ping(CN7) < 300) {
          user_sub_5();
        } else if (get_ping(CN10) < 300) {
          user_sub_7();
        } else {
          user_sub_3();
        }
      } else if (get_ping(CN7) < 400) {
        user_sub_5();
      } else if (get_ping(CN10) < 400) {
        user_sub_7();
      }
    } else if (get_timer(T1) > 900L) {
      gV[VAR_L] = 0;
      if (gAD[CN1] < 920) {
        if (gAD[CN2] < 920) {
          user_sub_7();
        } else if (gAD[CN3] < 920) {
          user_sub_5();
        } else if (gAD[CN5] < 920) {
          user_sub_7();
        } else {
          user_sub_2();
        }
      } else if (gAD[CN2] < 920) {
        if (gAD[CN4] < 920) {
          user_sub_5();
        } else {
          user_sub_3();
        }
      } else if (gAD[CN3] < 920) {
        if (gAD[CN4] < 920) {
          user_sub_4();
        } else {
          user_sub_5();
        }
      } else if (gAD[CN4] < 920) {
        user_sub_5();
      } else if (gAD[CN6] < 920) {
        user_sub_7();
      } else {
        user_sub_5();
      }
    }
  }
}
//--------------------------------------------------------------------------------
