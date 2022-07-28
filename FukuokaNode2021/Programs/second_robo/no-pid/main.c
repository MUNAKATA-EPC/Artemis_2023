//--------------------------------------------------------------------------------
// Title: Main - [ main ]
// Build:DAISEN C-Style for TJ3B  [ Ver.20190706 ] - [ Build_V190617 ]
//--------------------------------------------------------------------------------
// SetupVal:111111-333310-002002,cmt:
// CN01:IR_frontLeft
// CN02:IR_frontRight
// CN03:IR_left
// CN04:IR_right
// CN05:Line_sensor
// CN06:IR_front
// CN07:USS_Front
// CN08:USS_right
// CN09:USS_left
// CN10:USS_back
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
void user_sub_3(void);
void user_sub_4(void);
void user_main(void);
//--------------------------------------------------------------------------------
// Program Name : left.C
//--------------------------------------------------------------------------------
void user_sub_1(void)
{
  if (judge_bno(0, 0, 10)) {
    gPwm[0] = 0x35;
    gPwm[1] = 0x37 | 0x80;
    gPwm[2] = 0x32 | 0x80;
    gPwm[3] = 0x3F;
    pwm_out();
  } else if (judge_bno(0, 50, 40)) {
    gPwm[0] = 0x35;
    gPwm[1] = 0x37 | 0x80;
    gPwm[2] = 0x32;
    gPwm[3] = 0x3F;
    pwm_out();
  } else if (judge_bno(0, 135, 45)) {
    gPwm[0] = 0x35;
    gPwm[1] = 0x37 | 0x80;
    gPwm[2] = 0x32;
    gPwm[3] = 0x3F | 0x80;
    pwm_out();
  } else if (judge_bno(0, 225, 45)) {
    gPwm[0] = 0x35 | 0x80;
    gPwm[1] = 0x37;
    gPwm[2] = 0x32 | 0x80;
    gPwm[3] = 0x3F;
    pwm_out();
  } else if (judge_bno(0, 310, 40)) {
    gPwm[0] = 0x35;
    gPwm[1] = 0x37;
    gPwm[2] = 0x32 | 0x80;
    gPwm[3] = 0x3F;
    pwm_out();
  } else if (judge_bno(0, 360, 10)) {
    gPwm[0] = 0x35;
    gPwm[1] = 0x37 | 0x80;
    gPwm[2] = 0x32 | 0x80;
    gPwm[3] = 0x3F;
    pwm_out();
  }
}
//--------------------------------------------------------------------------------
// Program Name : back.C
//--------------------------------------------------------------------------------
void user_sub_2(void)
{
  if (judge_bno(0, 0, 10)) {
    gPwm[0] = 0x35;
    gPwm[1] = 0x37;
    gPwm[2] = 0x32;
    gPwm[3] = 0x3F;
    pwm_out();
  } else if (judge_bno(0, 50, 40)) {
    gPwm[0] = 0x35;
    gPwm[1] = 0x37;
    gPwm[2] = 0x32;
    gPwm[3] = 0x3F | 0x80;
    pwm_out();
  } else if (judge_bno(0, 135, 45)) {
    gPwm[0] = 0x35;
    gPwm[1] = 0x37 | 0x80;
    gPwm[2] = 0x32;
    gPwm[3] = 0x3F | 0x80;
    pwm_out();
  } else if (judge_bno(0, 225, 45)) {
    gPwm[0] = 0x35 | 0x80;
    gPwm[1] = 0x37;
    gPwm[2] = 0x32 | 0x80;
    gPwm[3] = 0x3F;
    pwm_out();
  } else if (judge_bno(0, 310, 40)) {
    gPwm[0] = 0x35 | 0x80;
    gPwm[1] = 0x37;
    gPwm[2] = 0x32;
    gPwm[3] = 0x3F;
    pwm_out();
  } else if (judge_bno(0, 360, 10)) {
    gPwm[0] = 0x35;
    gPwm[1] = 0x37;
    gPwm[2] = 0x32;
    gPwm[3] = 0x3F;
    pwm_out();
  }
}
//--------------------------------------------------------------------------------
// Program Name : front.C
//--------------------------------------------------------------------------------
void user_sub_3(void)
{
  if (judge_bno(0, 0, 10)) {
    gPwm[0] = 0x35 | 0x80;
    gPwm[1] = 0x37 | 0x80;
    gPwm[2] = 0x32 | 0x80;
    gPwm[3] = 0x3F | 0x80;
    pwm_out();
  } else if (judge_bno(0, 50, 40)) {
    gPwm[0] = 0x35;
    gPwm[1] = 0x37 | 0x80;
    gPwm[2] = 0x32 | 0x80;
    gPwm[3] = 0x3F | 0x80;
    pwm_out();
  } else if (judge_bno(0, 135, 45)) {
    gPwm[0] = 0x35;
    gPwm[1] = 0x37 | 0x80;
    gPwm[2] = 0x32;
    gPwm[3] = 0x3F | 0x80;
    pwm_out();
  } else if (judge_bno(0, 225, 45)) {
    gPwm[0] = 0x35 | 0x80;
    gPwm[1] = 0x37;
    gPwm[2] = 0x32 | 0x80;
    gPwm[3] = 0x3F;
    pwm_out();
  } else if (judge_bno(0, 310, 40)) {
    gPwm[0] = 0x35 | 0x80;
    gPwm[1] = 0x37 | 0x80;
    gPwm[2] = 0x32 | 0x80;
    gPwm[3] = 0x3F;
    pwm_out();
  } else if (judge_bno(0, 360, 10)) {
    gPwm[0] = 0x35 | 0x80;
    gPwm[1] = 0x37 | 0x80;
    gPwm[2] = 0x32 | 0x80;
    gPwm[3] = 0x3F | 0x80;
    pwm_out();
  }
}
//--------------------------------------------------------------------------------
// Program Name : right.C
//--------------------------------------------------------------------------------
void user_sub_4(void)
{
  if (judge_bno(0, 0, 10)) {
    gPwm[0] = 0x35 | 0x80;
    gPwm[1] = 0x37;
    gPwm[2] = 0x32;
    gPwm[3] = 0x3E | 0x80;
    pwm_out();
  } else if (judge_bno(0, 50, 40)) {
    gPwm[0] = 0x35;
    gPwm[1] = 0x37 | 0x80;
    gPwm[2] = 0x32;
    gPwm[3] = 0x3F;
    pwm_out();
  } else if (judge_bno(0, 135, 45)) {
    gPwm[0] = 0x35;
    gPwm[1] = 0x37 | 0x80;
    gPwm[2] = 0x32;
    gPwm[3] = 0x3F | 0x80;
    pwm_out();
  } else if (judge_bno(0, 225, 45)) {
    gPwm[0] = 0x35 | 0x80;
    gPwm[1] = 0x37;
    gPwm[2] = 0x32 | 0x80;
    gPwm[3] = 0x3F;
    pwm_out();
  } else if (judge_bno(0, 310, 40)) {
    gPwm[0] = 0x35;
    gPwm[1] = 0x37;
    gPwm[2] = 0x32 | 0x80;
    gPwm[3] = 0x3F;
    pwm_out();
  } else if (judge_bno(0, 360, 10)) {
    gPwm[0] = 0x35 | 0x80;
    gPwm[1] = 0x37;
    gPwm[2] = 0x32;
    gPwm[3] = 0x3F | 0x80;
    pwm_out();
  }
}
//--------------------------------------------------------------------------------
// Program Name : main.C
//--------------------------------------------------------------------------------
void user_main(void)
{
  while (TRUE) {
    user_sub_1();
    if (gAD[CN5] < 102) {
    } else {
      if (gAD[CN1] < 920) {
        if (gAD[CN3] < 920) {
          user_sub_2();
        } else if (gAD[CN2] < 920) {
          user_sub_3();
        } else if (gAD[CN6] < 920) {
          gPwm[0] = 0x32;
          gPwm[1] = 0x00;
          gPwm[2] = 0x00;
          gPwm[3] = 0x32;
          pwm_out();
        } else {
          user_sub_1();
        }
      } else if (gAD[CN2] < 920) {
        if (gAD[CN4] < 920) {
          user_sub_2();
        } else if (gAD[CN6] < 920) {
          gPwm[0] = 0x00;
          gPwm[1] = 0x32;
          gPwm[2] = 0x32;
          gPwm[3] = 0x00;
          pwm_out();
        } else {
          user_sub_4();
        }
      } else if (gAD[CN3] < 920) {
        if (gAD[CN4] < 920) {
          gPwm[0] = 0x32;
          gPwm[1] = 0x00;
          gPwm[2] = 0x00;
          gPwm[3] = 0x32;
          pwm_out();
        } else {
          gPwm[0] = 0x32;
          gPwm[1] = 0x00;
          gPwm[2] = 0x00;
          gPwm[3] = 0x32;
          pwm_out();
        }
      } else if (gAD[CN4] < 920) {
        gPwm[0] = 0x00;
        gPwm[1] = 0x32;
        gPwm[2] = 0x32;
        gPwm[3] = 0x00;
        pwm_out();
      } else if (gAD[CN6] < 920) {
        user_sub_3();
      } else {
      }
    }
  }
}
//--------------------------------------------------------------------------------
