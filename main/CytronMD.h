class CytronMD {
public:
  CytronMD(byte Pwm, byte Dir, byte pwm_chanel);
  void motor(int speed);

protected:
  byte pwm;
  byte dir;
  byte motor_pwm_chanel;
};