//--------------------------------------------------------------------------------
// Title: Main - [ main ]
// Build:DAISEN C-Style for TJ3B  [ Ver.20190706 ] - [ Build_V190617 ]
//--------------------------------------------------------------------------------
// SetupVal:111111-111110-000002,cmt:
// CN01:ir_ring
// CN02:gyro_sensor
// CN03:court_deg
// CN04:goal_deg
// CN05:goal_distance
// CN06:line_sensor
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
void user_sub_6(void);
void user_sub_9(void);
void user_sub_4(void);
void user_sub_8(void);
void user_sub_2(void);
void user_sub_3(void);
void user_sub_5(void);
void user_sub_10(void);
void user_sub_7(void);
void user_main(void);
//--------------------------------------------------------------------------------
// Program Name : pid-modoki.C
//--------------------------------------------------------------------------------
void user_sub_1(void)
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
// Program Name : front.C
//--------------------------------------------------------------------------------
void user_sub_6(void)
{
  gV[VAR_W] = 25;
  gV[VAR_X] = 25;
  gV[VAR_Y] = 25;
  gV[VAR_Z] = 25;
  gPwm[0] = gV[VAR_H] < 0 ? (gV[VAR_H] * -1) | 0x80 : gV[VAR_H];
  gPwm[1] = gV[VAR_I] < 0 ? (gV[VAR_I] * -1) | 0x80 : gV[VAR_I];
  gPwm[2] = gV[VAR_J] < 0 ? (gV[VAR_J] * -1) | 0x80 : gV[VAR_J];
  gPwm[3] = gV[VAR_K] < 0 ? (gV[VAR_K] * -1) | 0x80 : gV[VAR_K];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : rightfront.C
//--------------------------------------------------------------------------------
void user_sub_9(void)
{
  gV[VAR_W] = 0;
  gV[VAR_X] = 30;
  gV[VAR_Y] = 30;
  gV[VAR_Z] = 0;
  gPwm[0] = gV[VAR_H] < 0 ? (gV[VAR_H] * -1) | 0x80 : gV[VAR_H];
  gPwm[1] = gV[VAR_I] < 0 ? (gV[VAR_I] * -1) | 0x80 : gV[VAR_I];
  gPwm[2] = gV[VAR_J] < 0 ? (gV[VAR_J] * -1) | 0x80 : gV[VAR_J];
  gPwm[3] = gV[VAR_K] < 0 ? (gV[VAR_K] * -1) | 0x80 : gV[VAR_K];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : right.C
//--------------------------------------------------------------------------------
void user_sub_4(void)
{
  gV[VAR_W] = - 30;
  gV[VAR_X] = 30;
  gV[VAR_Y] = 30;
  gV[VAR_Z] = - 30;
  gPwm[0] = gV[VAR_H] < 0 ? (gV[VAR_H] * -1) | 0x80 : gV[VAR_H];
  gPwm[1] = gV[VAR_I] < 0 ? (gV[VAR_I] * -1) | 0x80 : gV[VAR_I];
  gPwm[2] = gV[VAR_J] < 0 ? (gV[VAR_J] * -1) | 0x80 : gV[VAR_J];
  gPwm[3] = gV[VAR_K] < 0 ? (gV[VAR_K] * -1) | 0x80 : gV[VAR_K];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : rightback.C
//--------------------------------------------------------------------------------
void user_sub_8(void)
{
  gV[VAR_W] = - 30;
  gV[VAR_X] = 0;
  gV[VAR_Y] = 0;
  gV[VAR_Z] = - 30;
  gPwm[0] = gV[VAR_H] < 0 ? (gV[VAR_H] * -1) | 0x80 : gV[VAR_H];
  gPwm[1] = gV[VAR_I] < 0 ? (gV[VAR_I] * -1) | 0x80 : gV[VAR_I];
  gPwm[2] = gV[VAR_J] < 0 ? (gV[VAR_J] * -1) | 0x80 : gV[VAR_J];
  gPwm[3] = gV[VAR_K] < 0 ? (gV[VAR_K] * -1) | 0x80 : gV[VAR_K];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : back.C
//--------------------------------------------------------------------------------
void user_sub_2(void)
{
  gV[VAR_W] = -35;
  gV[VAR_X] = -35;
  gV[VAR_Y] = -35;
  gV[VAR_Z] = -35;
  gPwm[0] = gV[VAR_H] < 0 ? (gV[VAR_H] * -1) | 0x80 : gV[VAR_H];
  gPwm[1] = gV[VAR_I] < 0 ? (gV[VAR_I] * -1) | 0x80 : gV[VAR_I];
  gPwm[2] = gV[VAR_J] < 0 ? (gV[VAR_J] * -1) | 0x80 : gV[VAR_J];
  gPwm[3] = gV[VAR_K] < 0 ? (gV[VAR_K] * -1) | 0x80 : gV[VAR_K];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : leftback.C
//--------------------------------------------------------------------------------
void user_sub_3(void)
{
  gV[VAR_W] = 0;
  gV[VAR_X] = -30;
  gV[VAR_Y] = -30;
  gV[VAR_Z] = 0;
  gPwm[0] = gV[VAR_H] < 0 ? (gV[VAR_H] * -1) | 0x80 : gV[VAR_H];
  gPwm[1] = gV[VAR_I] < 0 ? (gV[VAR_I] * -1) | 0x80 : gV[VAR_I];
  gPwm[2] = gV[VAR_J] < 0 ? (gV[VAR_J] * -1) | 0x80 : gV[VAR_J];
  gPwm[3] = gV[VAR_K] < 0 ? (gV[VAR_K] * -1) | 0x80 : gV[VAR_K];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : left.C
//--------------------------------------------------------------------------------
void user_sub_5(void)
{
  gV[VAR_W] = 30;
  gV[VAR_X] = - 30;
  gV[VAR_Y] = - 30;
  gV[VAR_Z] = 30;
  gPwm[0] = gV[VAR_H] < 0 ? (gV[VAR_H] * -1) | 0x80 : gV[VAR_H];
  gPwm[1] = gV[VAR_I] < 0 ? (gV[VAR_I] * -1) | 0x80 : gV[VAR_I];
  gPwm[2] = gV[VAR_J] < 0 ? (gV[VAR_J] * -1) | 0x80 : gV[VAR_J];
  gPwm[3] = gV[VAR_K] < 0 ? (gV[VAR_K] * -1) | 0x80 : gV[VAR_K];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : leftfront.C
//--------------------------------------------------------------------------------
void user_sub_10(void)
{
  gV[VAR_W] = 30;
  gV[VAR_X] = 0;
  gV[VAR_Y] = 0;
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
void user_sub_7(void)
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
  gV[VAR_S] = 1;  	// ”ä—áƒQƒCƒ“
  gV[VAR_T] = 20;  	// ”÷•ªƒQƒCƒ“
  while (TRUE) {
    user_sub_1();
    if (gAD[CN6] < 102) {
      if (gV[VAR_M] == 0) {
        clr_timer(0);
        gV[VAR_M] = 1;
      }
    }
    if (get_timer(T1) < 200L) {
      gPwm[0] = 0x00 | 0x80;
      gPwm[1] = 0x00 | 0x80;
      gPwm[2] = 0x00 | 0x80;
      gPwm[3] = 0x00 | 0x80;
      pwm_out();
    } else if (get_timer(T1) < 500L) {
      if (gAD[CN3] < 245) {
        user_sub_6();
      } else if (gAD[CN3] < 276) {
        user_sub_9();
      } else if (gAD[CN3] < 317) {
        user_sub_4();
      } else if (gAD[CN3] < 419) {
        user_sub_8();
      } else if (gAD[CN3] < 460) {
        user_sub_2();
      } else if (gAD[CN3] < 552) {
        user_sub_3();
      } else if (gAD[CN3] < 716) {
        user_sub_5();
      } else if (gAD[CN3] < 777) {
        user_sub_10();
      } else if (gAD[CN3] < 797) {
        user_sub_6();
      }
    } else {
      gV[VAR_M] = 0;
      if (gAD[CN3] < 767) {
        gV[VAR_O] = 0;
        if (gAD[CN3] < 225) {
          user_sub_6();
        } else if (gAD[CN3] < 286) {
          user_sub_4();
        } else if (gAD[CN3] < 337) {
          user_sub_8();
        } else if (gAD[CN3] < 409) {
          user_sub_2();
        } else if (gAD[CN3] < 470) {
          user_sub_3();
        } else if (gAD[CN3] < 552) {
          user_sub_8();
        } else if (gAD[CN3] < 593) {
          user_sub_2();
        } else if (gAD[CN3] < 634) {
          user_sub_3();
        } else if (gAD[CN3] < 716) {
          user_sub_5();
        } else if (gAD[CN3] < 767) {
          user_sub_6();
        }
      } else {
        user_sub_7();
      }
    }
  }
}
//--------------------------------------------------------------------------------
