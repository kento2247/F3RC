#include "Arduino.h"
#include "CytronMD.h"

CytronMD::CytronMD(byte Pwm, byte Dir, byte pwm_chanel) {
  pwm = Pwm;
  dir = Dir;
  motor_pwm_chanel = pwm_chanel;
  pinMode(dir, OUTPUT);
  ledcSetup(motor_pwm_chanel, 10000, 8);  // 10kHz、7bit
  ledcAttachPin(pwm, motor_pwm_chanel);
}

void CytronMD::motor(int speed) {
  //-128〜127で速度と方向を指定
  if (speed < 0) {
    digitalWrite(dir, 0);
  } else {
    digitalWrite(dir, 1);
  }
  byte new_speed = abs(speed);
  ledcWrite(motor_pwm_chanel, constrain(new_speed, 0, 127));
}