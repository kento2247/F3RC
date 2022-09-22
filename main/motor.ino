void motor_control(int LY, int LX, int RX) {
  float rad = atan2(LY, LX);
  float len = sqrt(LX * LX + LY * LY) * 16;
  len = constrain(len, 0, 127);
  int m1_speed = (1 * cos(rad + PI / 4) * len);
  int m2_speed = (-1 * sin(rad + PI / 4) * len);
  int m3_speed = (-1 * m2_speed);
  int m4_speed = (1 * m1_speed);

  int motor_speed[4] = { //-128~127の範囲でない可能性あり
                         m1_speed, m2_speed, m3_speed, m4_speed
  };
  if (RX != 0) {
    int turn = RX * 16;
    int turn_step = 0;
    if (RX > 0) turn_step = 1;
    else turn_step = -1;
    bool escape_flag = 0;
    while (1) {
      for (byte i = 0; i < 4; i++) {
        if (abs(motor_speed[i]) >= 254) {
          escape_flag = 1;
          break;
        }
        if (i == 0 || i == 3) {
          motor_speed[i] -= turn_step;
        } else {
          motor_speed[i] += turn_step;
        }
      }
      if (escape_flag) break;
      turn -= turn_step;
      if (turn == 0) break;
    }
    m1_speed = motor_speed[0];
    m2_speed = motor_speed[1];
    m3_speed = motor_speed[2];
    m4_speed = motor_speed[3];
  }

  show_data(rad, len, m1_speed, m2_speed, m3_speed, m4_speed, RX);
  motor_1.motor(m1_speed);
  motor_2.motor(m2_speed);
  motor_3.motor(m3_speed);
  motor_4.motor(m4_speed);
}

//デバック用
void show_data(float rad, float len, int m1_speed, int m2_speed, int m3_speed, int m4_speed, int RX) {
  Serial.print("rad = ");
  Serial.print(rad * 180 / PI);
  Serial.print(", ");
  Serial.print("len = ");
  Serial.print(len);
  Serial.print(", ");

  //  Serial.print("m1=");
  Serial.print(m1_speed);
  Serial.print(", ");
  //  Serial.print("m2=");
  Serial.print(m2_speed);
  Serial.print(", ");
  //  Serial.print("m3=");
  Serial.print(m3_speed);
  Serial.print(", ");
  //  Serial.print("m4=");
  Serial.print(m4_speed);
  Serial.print(", ");
  //  Serial.print("RX=");
  // Serial.println(RX);
  Serial.println();
}

void emergency_stop_motor() {
  motor_1.motor(0);
  motor_2.motor(0);
  motor_3.motor(0);
  motor_4.motor(0);
}

void cyutrial() {
  int speed_4 = 0;
  while (1) {
    speed_4 += 1;
    motor_4.motor(speed_4);
    motor_3.motor(speed_4);
    motor_2.motor(speed_4);
    motor_1.motor(speed_4);
    Serial.println(int(speed_4));
    delay(30);
    if (speed_4 >= 128) speed_4 = -128;
  }
}