//--------------------------------------------------------------------------------
// Title: Main - [ Main ]
// Build:DAISEN C-Style for TJ3B  [ Ver.20190706 ] - [ Build_V190617 ]
//--------------------------------------------------------------------------------
// SetupVal:111111-333310-002002,cmt:
// CN01:
// CN02:
// CN03:
// CN04:
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
// Functions
//--------------------------------------------------------------------------------
void user_sub_2(void);
void user_sub_6(void);
void user_sub_3(void);
void user_sub_4(void);
void user_sub_5(void);
void user_sub_7(void);
void user_sub_8(void);
void user_sub_1(void);
void user_main(void);
//--------------------------------------------------------------------------------
// Program Name : Move-Stop.C
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
// Program Name : Move-Back.C
//--------------------------------------------------------------------------------
void user_sub_6(void)
{
  gV[VAR_W] = 0;
  gV[VAR_X] = 0;
  gV[VAR_Y] = 60;
  gV[VAR_Z] = -60;
  gPwm[0] = gV[VAR_H] < 0 ? (gV[VAR_H] * -1) | 0x80 : gV[VAR_H];
  gPwm[1] = gV[VAR_I] < 0 ? (gV[VAR_I] * -1) | 0x80 : gV[VAR_I];
  gPwm[2] = gV[VAR_J] < 0 ? (gV[VAR_J] * -1) | 0x80 : gV[VAR_J];
  gPwm[3] = gV[VAR_K] < 0 ? (gV[VAR_K] * -1) | 0x80 : gV[VAR_K];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : Move-Front.C
//--------------------------------------------------------------------------------
void user_sub_3(void)
{
  gV[VAR_W] = 0;
  gV[VAR_X] = 0;
  gV[VAR_Y] = -50;
  gV[VAR_Z] = 50;
  gPwm[0] = gV[VAR_H] < 0 ? (gV[VAR_H] * -1) | 0x80 : gV[VAR_H];
  gPwm[1] = gV[VAR_I] < 0 ? (gV[VAR_I] * -1) | 0x80 : gV[VAR_I];
  gPwm[2] = gV[VAR_J] < 0 ? (gV[VAR_J] * -1) | 0x80 : gV[VAR_J];
  gPwm[3] = gV[VAR_K] < 0 ? (gV[VAR_K] * -1) | 0x80 : gV[VAR_K];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : Move-Left.C
//--------------------------------------------------------------------------------
void user_sub_4(void)
{
  gV[VAR_W] = 60;
  gV[VAR_X] = -60;
  gV[VAR_Y] = 0;
  gV[VAR_Z] = 0;
  gPwm[0] = gV[VAR_H] < 0 ? (gV[VAR_H] * -1) | 0x80 : gV[VAR_H];
  gPwm[1] = gV[VAR_I] < 0 ? (gV[VAR_I] * -1) | 0x80 : gV[VAR_I];
  gPwm[2] = gV[VAR_J] < 0 ? (gV[VAR_J] * -1) | 0x80 : gV[VAR_J];
  gPwm[3] = gV[VAR_K] < 0 ? (gV[VAR_K] * -1) | 0x80 : gV[VAR_K];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : Move-Right.C
//--------------------------------------------------------------------------------
void user_sub_5(void)
{
  gV[VAR_W] = -60;
  gV[VAR_X] = 60;
  gV[VAR_Y] = 0;
  gV[VAR_Z] = 0;
  gPwm[0] = gV[VAR_H] < 0 ? (gV[VAR_H] * -1) | 0x80 : gV[VAR_H];
  gPwm[1] = gV[VAR_I] < 0 ? (gV[VAR_I] * -1) | 0x80 : gV[VAR_I];
  gPwm[2] = gV[VAR_J] < 0 ? (gV[VAR_J] * -1) | 0x80 : gV[VAR_J];
  gPwm[3] = gV[VAR_K] < 0 ? (gV[VAR_K] * -1) | 0x80 : gV[VAR_K];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : Move-LeftBack.C
//--------------------------------------------------------------------------------
void user_sub_7(void)
{
  gV[VAR_W] = 60;
  gV[VAR_X] = -60;
  gV[VAR_Y] = 60;
  gV[VAR_Z] = -60;
  gPwm[0] = gV[VAR_H] < 0 ? (gV[VAR_H] * -1) | 0x80 : gV[VAR_H];
  gPwm[1] = gV[VAR_I] < 0 ? (gV[VAR_I] * -1) | 0x80 : gV[VAR_I];
  gPwm[2] = gV[VAR_J] < 0 ? (gV[VAR_J] * -1) | 0x80 : gV[VAR_J];
  gPwm[3] = gV[VAR_K] < 0 ? (gV[VAR_K] * -1) | 0x80 : gV[VAR_K];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : Move-RightBack.C
//--------------------------------------------------------------------------------
void user_sub_8(void)
{
  gV[VAR_W] = -60;
  gV[VAR_X] = 60;
  gV[VAR_Y] = 60;
  gV[VAR_Z] = -60;
  gPwm[0] = gV[VAR_H] < 0 ? (gV[VAR_H] * -1) | 0x80 : gV[VAR_H];
  gPwm[1] = gV[VAR_I] < 0 ? (gV[VAR_I] * -1) | 0x80 : gV[VAR_I];
  gPwm[2] = gV[VAR_J] < 0 ? (gV[VAR_J] * -1) | 0x80 : gV[VAR_J];
  gPwm[3] = gV[VAR_K] < 0 ? (gV[VAR_K] * -1) | 0x80 : gV[VAR_K];
  pwm_out();
}
//--------------------------------------------------------------------------------
// Program Name : PID§Œä‚à‚Ç‚«.C
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
  gV[VAR_I] = gV[VAR_X] + gV[VAR_F];
  gV[VAR_J] = gV[VAR_Y] + gV[VAR_F];
  gV[VAR_K] = gV[VAR_Z] + gV[VAR_F];
}
//--------------------------------------------------------------------------------
// Program Name : Main.C
//--------------------------------------------------------------------------------
void user_main(void)
{
  gV[VAR_S] = 1;  	// ”ä—áƒQƒCƒ“
  gV[VAR_T] = 6;  	// ”÷•ªƒQƒCƒ“
  while (TRUE) {
    if (gAD[CN6] < 102) {
      clr_timer(0);
      set_Led(1, LED_ON);
      if (get_timer(T1) < 500L) {
        user_sub_2();
      }
      if (get_timer(T1) > 500L) {
        clr_timer(1);
        if (get_timer(T2) < 500L) {
          if (get_ping(CN8) < 400) {
            if (get_ping(CN7) < 400) {
              user_sub_6();
            } else if (get_ping(CN10) < 400) {
              user_sub_3();
            } else {
              user_sub_4();
            }
          } else if (get_ping(CN9) < 400) {
            if (get_ping(CN7) < 400) {
              user_sub_6();
            } else if (get_ping(CN10) < 400) {
              user_sub_3();
            } else {
              user_sub_5();
            }
          } else if (get_ping(CN10) > 400) {
            user_sub_3();
          } else if (get_ping(CN10) < 400) {
            user_sub_2();
          }
        }
      }
    } else {
      set_Led(1, LED_OFF);
      if (gAD[CN1] < 971) {
        if (gAD[CN2] < 971) {
          if (gAD[CN3] > 920) {
            if (gAD[CN4] > 920) {
              user_sub_3();
            } else {
              user_sub_5();
            }
          } else {
            if (gAD[CN4] > 920) {
              user_sub_4();
            } else {
              user_sub_3();
            }
          }
        } else if (gAD[CN3] < 920) {
          user_sub_7();
        } else {
          user_sub_4();
        }
      } else if (gAD[CN2] < 971) {
        if (gAD[CN4] < 920) {
          user_sub_8();
        } else {
          user_sub_5();
        }
      } else if (gAD[CN3] < 920) {
        if (gAD[CN5] < 920) {
          user_sub_8();
        } else {
          user_sub_6();
        }
      } else if (gAD[CN4] < 920) {
        if (gAD[CN5] < 920) {
          user_sub_7();
        } else {
          user_sub_6();
        }
      } else if (gAD[CN5] < 920) {
        user_sub_7();
      } else {
        if (get_ping(CN10) > 400) {
          user_sub_6();
        } else {
          user_sub_2();
        }
      }
    }
    user_sub_1();
  }
}
//--------------------------------------------------------------------------------
