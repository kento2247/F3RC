void motor_control(char LY, char LX, char R_X) {
  double rad = atan2(LY, LX);
  double len = sqrt(LX * LX + LY * LY);
  int m1_speed = (-1 * cos(rad + PI / 4) * len);
  int m2_speed = (-1 * sin(rad + PI / 4) * len);
  int m3_speed = (-1 * m2_speed);
  int m4_speed = (-1 * m1_speed);
  show_data(rad, len, m1_speed, m2_speed, m3_speed, m4_speed);

  int motor_speed[4] = { //-128~127の範囲でない可能性あり
    m1_speed, m2_speed, m3_speed, m4_speed
  };
  char turn = R_X;
  char turn_step = 0;
  if (turn > 0) turn_step = 1;
  else turn_step = -1;
  bool escape_flag = 0;
  while (1) {
    for (byte i = 0; i < 4; i++) {
      if (abs(motor_speed[i]) >= 127) {
        escape_flag = 1;
        break;
      }
      motor_speed[i] -= turn_step;
    }
    if (escape_flag) break;
    m1_speed = motor_speed[0];
    m2_speed = motor_speed[1];
    m3_speed = motor_speed[2];
    m4_speed = motor_speed[3];
    turn -= turn_step;
    if (turn == 0) break;
  }

  show_data(rad, len, m1_speed, m2_speed, m3_speed, m4_speed);
  
  motor_1.motor(m1_speed);
  motor_2.motor(m2_speed);
  motor_3.motor(m3_speed);
  motor_4.motor(m4_speed);
}

//デバック用
void show_data(double rad, double len, int m1_speed, int m2_speed, int m3_speed, int m4_speed) {
  Serial.print("rad = ");
  Serial.print(rad * 180 / PI);
  Serial.print(",  len = ");
  Serial.println(len);

  Serial.print("m1=");
  Serial.print(m1_speed);
  Serial.print(", ");
  Serial.print("m2=");
  Serial.print(m2_speed);
  Serial.print(", ");
  Serial.print("m3=");
  Serial.print(m3_speed);
  Serial.print(", ");
  Serial.print("m4=");
  Serial.println(m4_speed);
  Serial.println();
}
