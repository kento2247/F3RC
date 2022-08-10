#include "CytronMotorDriver.h"

CytronMD::CytronMD(PinName Pwm, PinName Dir) : pwm(Pwm), dir(Dir) {
  pwm.period_us(100);  //周期設定
}

void CytronMD::speed(float speed) {
  //-1〜1で速度と方向を指定
  if (speed < 0) {
    dir = 0;
  } else {
    dir = 1;
  }
  pwm = abs(speed);
}
