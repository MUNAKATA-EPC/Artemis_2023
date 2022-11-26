//--------------------------------------------------------------------------------
// Title: Main - [ main_second ]
// Build:DAISEN C-Style for TJ3B  [ Ver.20190706 ] - [ Build_V190617 ]
//--------------------------------------------------------------------------------
// SetupVal:111111-111110-000002,cmt:
// CN01:IR_Deg
// CN02:IR_Distance
// CN03:
// CN04:
// CN05:
// CN06:Line
// CN07:Gyro
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
void user_sub_8(void);
void user_sub_11(void);
void user_sub_12(void);
void user_sub_9(void);
void user_sub_4(void);
void user_sub_5(void);
void user_sub_6(void);
void user_sub_10(void);
void user_sub_7(void);
void user_sub_3(void);
void user_sub_13(void);
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
// Program Name : front.C
//--------------------------------------------------------------------------------
void user_sub_2(void)
{
  gV[VAR_W] = 30;
  gV[VAR_X] = 30;
  gV[VAR_Y] = 30;
  gV[VAR_Z] = 30;
  gPwm[0] = gV[VAR_H] < 0 ? (gV[VAR_H] * -1) | 0x80 : gV[VAR_H];
  gPwm[1] = gV[VAR_I] < 0 ? (gV[VAR_I] * -1) | 0x80 : gV[VAR_I];
  gPwm[2] = gV[VAR_J] < 0 ? (gV[VAR_J] * -1) | 0x80 : gV[VAR_J];
  gPwm[3] = gV[VAR_K] < 0 ? (gV[VAR_K] * -1) | 0x80 : gV[VAR_K];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : rightfront.C
//--------------------------------------------------------------------------------
void user_sub_8(void)
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
void user_sub_11(void)
{
  gV[VAR_W] = - 32;
  gV[VAR_X] = 32;
  gV[VAR_Y] = 32;
  gV[VAR_Z] = - 32;
  gPwm[0] = gV[VAR_H] < 0 ? (gV[VAR_H] * -1) | 0x80 : gV[VAR_H];
  gPwm[1] = gV[VAR_I] < 0 ? (gV[VAR_I] * -1) | 0x80 : gV[VAR_I];
  gPwm[2] = gV[VAR_J] < 0 ? (gV[VAR_J] * -1) | 0x80 : gV[VAR_J];
  gPwm[3] = gV[VAR_K] < 0 ? (gV[VAR_K] * -1) | 0x80 : gV[VAR_K];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : left.C
//--------------------------------------------------------------------------------
void user_sub_12(void)
{
  gV[VAR_W] = 35;
  gV[VAR_X] = - 35;
  gV[VAR_Y] = - 35;
  gV[VAR_Z] = 35;
  gPwm[0] = gV[VAR_H] < 0 ? (gV[VAR_H] * -1) | 0x80 : gV[VAR_H];
  gPwm[1] = gV[VAR_I] < 0 ? (gV[VAR_I] * -1) | 0x80 : gV[VAR_I];
  gPwm[2] = gV[VAR_J] < 0 ? (gV[VAR_J] * -1) | 0x80 : gV[VAR_J];
  gPwm[3] = gV[VAR_K] < 0 ? (gV[VAR_K] * -1) | 0x80 : gV[VAR_K];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : leftfront.C
//--------------------------------------------------------------------------------
void user_sub_9(void)
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
// Program Name : rightback.C
//--------------------------------------------------------------------------------
void user_sub_4(void)
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
// Program Name : back.C
//--------------------------------------------------------------------------------
void user_sub_5(void)
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
// Program Name : leftback.C
//--------------------------------------------------------------------------------
void user_sub_6(void)
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
// Program Name : front_slow.C
//--------------------------------------------------------------------------------
void user_sub_10(void)
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
// Program Name : left_slow.C
//--------------------------------------------------------------------------------
void user_sub_7(void)
{
  gV[VAR_W] = 20;
  gV[VAR_X] = - 20;
  gV[VAR_Y] = - 20;
  gV[VAR_Z] = 20;
  gPwm[0] = gV[VAR_H] < 0 ? (gV[VAR_H] * -1) | 0x80 : gV[VAR_H];
  gPwm[1] = gV[VAR_I] < 0 ? (gV[VAR_I] * -1) | 0x80 : gV[VAR_I];
  gPwm[2] = gV[VAR_J] < 0 ? (gV[VAR_J] * -1) | 0x80 : gV[VAR_J];
  gPwm[3] = gV[VAR_K] < 0 ? (gV[VAR_K] * -1) | 0x80 : gV[VAR_K];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : right_slow.C
//--------------------------------------------------------------------------------
void user_sub_3(void)
{
  gV[VAR_W] = - 20;
  gV[VAR_X] = 20;
  gV[VAR_Y] = 20;
  gV[VAR_Z] = - 20;
  gPwm[0] = gV[VAR_H] < 0 ? (gV[VAR_H] * -1) | 0x80 : gV[VAR_H];
  gPwm[1] = gV[VAR_I] < 0 ? (gV[VAR_I] * -1) | 0x80 : gV[VAR_I];
  gPwm[2] = gV[VAR_J] < 0 ? (gV[VAR_J] * -1) | 0x80 : gV[VAR_J];
  gPwm[3] = gV[VAR_K] < 0 ? (gV[VAR_K] * -1) | 0x80 : gV[VAR_K];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : stop.C
//--------------------------------------------------------------------------------
void user_sub_13(void)
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
// Program Name : main_second.C
//--------------------------------------------------------------------------------
void user_main(void)
{
  while (TRUE) {
    user_sub_1();
    if (gAD[CN6] < 102) {
      if (gV[VAR_L] == 0) {
        clr_timer(0);
        gV[VAR_L] = 1;
      }
    } else {
      if (get_timer(T1) < 300L) {
        gPwm[0] = 0x00 | 0x80;
        gPwm[1] = 0x00 | 0x80;
        gPwm[2] = 0x00 | 0x80;
        gPwm[3] = 0x00 | 0x80;
        pwm_out();
      } else if (get_timer(T1) < 600L) {
        if (gAD[CN3] < 286) {
          if (gAD[CN1] < 51) {
            user_sub_2();
          } else if (gAD[CN1] < 153) {
            user_sub_8();
          } else if (gAD[CN1] < 245) {
            user_sub_11();
          } else if (gAD[CN1] < 552) {
          } else if (gAD[CN1] < 664) {
            user_sub_12();
          } else if (gAD[CN1] < 716) {
            user_sub_9();
          } else {
            user_sub_2();
          }
        } else if (gAD[CN3] < 409) {
          user_sub_8();
        } else if (gAD[CN3] < 439) {
          user_sub_11();
        } else if (gAD[CN3] < 470) {
          user_sub_4();
        } else if (gAD[CN3] < 511) {
          user_sub_5();
        } else if (gAD[CN3] < 552) {
          user_sub_6();
        } else if (gAD[CN3] < 716) {
          user_sub_12();
        } else if (gAD[CN3] < 859) {
          user_sub_9();
        }
      } else {
        gV[VAR_L] = 0;
        if (gAD[CN2] < 450) {
          if (gAD[CN1] < 51) {
            if (gAD[CN8] > 920) {
              user_sub_10();
            } else {
              user_sub_2();
            }
          } else if (gAD[CN1] < 102) {
            if (gAD[CN2] < 439) {
              user_sub_8();
            } else {
              user_sub_11();
            }
          } else if (gAD[CN1] < 194) {
            user_sub_4();
          } else if (gAD[CN1] < 245) {
            user_sub_5();
          } else if (gAD[CN1] < 388) {
            user_sub_6();
          } else if (gAD[CN1] < 470) {
            user_sub_4();
          } else if (gAD[CN1] < 531) {
            user_sub_5();
          } else if (gAD[CN1] < 613) {
            user_sub_6();
          } else if (gAD[CN1] < 705) {
            if (gAD[CN2] < 388) {
              user_sub_9();
            } else {
              user_sub_7();
            }
          } else if (gAD[CN1] < 716) {
            user_sub_7();
          } else if (gAD[CN1] < 767) {
            user_sub_2();
          }
        } else if (gAD[CN2] < 542) {
          if (gAD[CN1] < 61) {
            user_sub_2();
          } else if (gAD[CN1] < 143) {
            if (gAD[CN2] < 480) {
              user_sub_3();
            } else {
              user_sub_8();
            }
          } else if (gAD[CN1] < 235) {
            if (gAD[CN2] < 501) {
              user_sub_4();
            } else {
              user_sub_11();
            }
          } else if (gAD[CN1] < 286) {
            user_sub_4();
          } else if (gAD[CN1] < 337) {
            user_sub_5();
          } else if (gAD[CN1] < 368) {
            user_sub_6();
          } else if (gAD[CN1] < 511) {
            user_sub_5();
          } else if (gAD[CN1] < 562) {
            user_sub_6();
          } else if (gAD[CN1] < 593) {
            user_sub_12();
          } else if (gAD[CN1] < 757) {
            user_sub_9();
          }
        } else {
          if (gAD[CN4] > 245) {
            user_sub_11();
          } else if (gAD[CN4] < 767) {
            user_sub_12();
          } else if (gAD[CN5] < 613) {
            user_sub_5();
          } else {
            user_sub_13();
          }
        }
      }
    }
  }
}
//--------------------------------------------------------------------------------
