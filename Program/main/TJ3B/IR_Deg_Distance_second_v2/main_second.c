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
void user_sub_4(void);
void user_sub_5(void);
void user_sub_6(void);
void user_sub_12(void);
void user_sub_9(void);
void user_sub_10(void);
void user_sub_3(void);
void user_sub_7(void);
void user_sub_13(void);
void user_sub_14(void);
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
  gV[VAR_W] = 20;
  gV[VAR_X] = 20;
  gV[VAR_Y] = 20;
  gV[VAR_Z] = 20;
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
  gV[VAR_X] = 25;
  gV[VAR_Y] = 25;
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
  gV[VAR_W] = 25;
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
// Program Name : front_slow.C
//--------------------------------------------------------------------------------
void user_sub_10(void)
{
  gV[VAR_W] = 20;
  gV[VAR_X] = 20;
  gV[VAR_Y] = 20;
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
// Program Name : back_slow.C
//--------------------------------------------------------------------------------
void user_sub_13(void)
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
void user_sub_14(void)
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
      } else if (get_timer(T1) < 800L) {
        if (gAD[CN3] < 286) {
          user_sub_2();
        } else if (gAD[CN3] < 368) {
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
            if (gAD[CN5] < 439) {
              if (gAD[CN4] < 225) {
                user_sub_10();
              } else if (gAD[CN4] < 306) {
                if (gAD[CN8] > 920) {
                  user_sub_8();
                } else {
                  user_sub_10();
                }
              } else if (gAD[CN4] < 716) {
              } else if (gAD[CN4] < 797) {
                if (gAD[CN8] > 920) {
                  user_sub_9();
                } else {
                  user_sub_10();
                }
              } else {
                user_sub_10();
              }
            } else if (gAD[CN5] < 358) {
              if (gAD[CN4] < 204) {
                user_sub_2();
              } else if (gAD[CN4] < 306) {
                if (gAD[CN8] > 920) {
                  gPwm[0] = 0x19;
                  gPwm[1] = 0x23;
                  gPwm[2] = 0x23;
                  gPwm[3] = 0x19;
                  pwm_out();
                } else {
                  user_sub_10();
                }
              } else if (gAD[CN4] < 716) {
              } else if (gAD[CN4] < 838) {
                if (gAD[CN8] > 920) {
                  gPwm[0] = 0x23;
                  gPwm[1] = 0x19;
                  gPwm[2] = 0x19;
                  gPwm[3] = 0x23;
                  pwm_out();
                } else {
                  user_sub_10();
                }
              } else {
                user_sub_10();
              }
            } else {
              user_sub_2();
            }
          } else if (gAD[CN1] < 102) {
            if (gAD[CN2] < 439) {
              user_sub_3();
            } else {
              user_sub_11();
            }
          } else if (gAD[CN1] < 194) {
            user_sub_4();
          } else if (gAD[CN1] < 245) {
            user_sub_5();
          } else if (gAD[CN1] < 388) {
            user_sub_6();
          } else if (gAD[CN1] < 521) {
            user_sub_4();
          } else if (gAD[CN1] < 572) {
            user_sub_5();
          } else if (gAD[CN1] < 613) {
            user_sub_6();
          } else if (gAD[CN1] < 716) {
            user_sub_7();
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
            user_sub_11();
          } else if (gAD[CN1] < 286) {
            user_sub_4();
          } else if (gAD[CN1] < 306) {
            user_sub_5();
          } else if (gAD[CN1] < 368) {
            user_sub_6();
          } else if (gAD[CN1] < 429) {
            user_sub_11();
          } else if (gAD[CN1] < 491) {
            user_sub_5();
          } else if (gAD[CN1] < 521) {
            user_sub_5();
          } else if (gAD[CN1] < 562) {
            user_sub_12();
          } else if (gAD[CN1] < 593) {
            user_sub_6();
          } else if (gAD[CN1] < 624) {
            user_sub_9();
          }
        } else {
          if (gAD[CN4] > 501) {
            if (gAD[CN4] < 531) {
              if (gAD[CN5] < 634) {
                if (gAD[CN5] < 480) {
                  user_sub_5();
                } else {
                  user_sub_13();
                }
              } else {
                user_sub_14();
              }
            } else {
              user_sub_4();
            }
          } else {
            if (gAD[CN4] < 460) {
              user_sub_6();
            } else {
              if (gAD[CN5] < 634) {
                if (gAD[CN5] < 480) {
                  user_sub_5();
                } else {
                  user_sub_13();
                }
              } else {
                user_sub_14();
              }
            }
          }
        }
      }
    }
  }
}
//--------------------------------------------------------------------------------
