#include <mbed.h>

class CytronMD {
 public:
  CytronMD(PinName Pwm, PinName Dir);
  void speed(float speed);

 protected:
  PwmOut pwm;  //初期化
  DigitalOut dir;
};
