#include <PS4Controller.h>
#include "CytronMD.h"
#define data_length 4
byte send_data[data_length];
byte encoded_data[data_length+2];
#define pwm_1 1  //pin指定
#define pwm_2 1  //pin指定
#define pwm_3 1  //pin指定
#define pwm_4 1  //pin指定
#define dir_1 2  //pin指定
#define dir_2 2  //pin指定
#define dir_3 2  //pin指定
#define dir_4 2  //pin指定
CytronMD motor_1 = CytronMD(pwm_1, dir_1);
CytronMD motor_2 = CytronMD(pwm_2, dir_2);
CytronMD motor_3 = CytronMD(pwm_3, dir_3);
CytronMD motor_4 = CytronMD(pwm_4, dir_4);

void setup() {
  Serial.begin(115200); //デバック用
  Serial2.begin(115200);
  PS4.begin("24:62:AB:FB:15:1A");
}

void loop() {
  if (PS4.isConnected()) {
    reload_controler_data();
    cobs_encode();
    Serial2.write((byte*)encoded_data, sizeof(encoded_data));

    motor_control(PS4.LStickY(), PS4.LStickX(), PS4.RStickX());
  }
}

void cobs_encode() {
  byte array_length = sizeof(encoded_data);
  encoded_data[0] = 0;
  encoded_data[array_length - 1] = 0;
  for (byte i = 1; i < array_length - 1; i++) {
    encoded_data[i] = send_data[i - 1];
  }

  byte zero_counter = array_length - 1;
  for (int i = array_length - 1; i >= 0; i--) {
    if (encoded_data[i] == 0) {
      encoded_data[i] = zero_counter - i;
      zero_counter = i;
    }
  }
}

void reload_controler_data() {
  send_data[0] = PS4.Circle();
  send_data[1] = PS4.Cross();
  send_data[2] = PS4.Triangle();
  send_data[3] = PS4.Square();
}
