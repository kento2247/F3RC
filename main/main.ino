#include <PS4Controller.h>
#include <Servo.h>
#include "CytronMD.h"

//pin割り当て
#define magnetic_valve 2
#define magnetic_open_valve 23
// #define emergency_stop 15
#define back_buzzer_pin 5
#define servo_pin1 18
#define servo_pin2 19
//1,3,16,17はHardwareserialで使用するため割り当て不可
//4,21,22,36,39は使用可能。34,35は多分使用可能

#define pwm_1 33  //pin指定
#define pwm_2 26  //pin指定
#define pwm_3 14  //pin指定
#define pwm_4 12  //pin指定
#define dir_1 32  //pin指定
#define dir_2 25  //pin指定　//なぜかバグる
#define dir_3 27  //pin指定  //なぜかバグる
#define dir_4 13  //pin指定
//環境変数
#define Serial_data_length 4
#define m1_pwm_chanel 12
#define m2_pwm_chanel 13
#define m3_pwm_chanel 14
#define m4_pwm_chanel 15
#define esp_bluetooth_mac "24:62:AB:FB:15:1A"

CytronMD motor_1 = CytronMD(pwm_1, dir_1, m1_pwm_chanel);
CytronMD motor_2 = CytronMD(pwm_2, dir_2, m2_pwm_chanel);
CytronMD motor_3 = CytronMD(pwm_3, dir_3, m3_pwm_chanel);
CytronMD motor_4 = CytronMD(pwm_4, dir_4, m4_pwm_chanel);
Servo servoMotor1;
Servo servoMotor2;

void setup() {
  Serial.begin(115200);  //デバック用
  // Serial2.begin(115200);
  PS4.begin(esp_bluetooth_mac);
  pinMode(magnetic_valve, OUTPUT);
  // pinMode(emergency_stop, OUTPUT);
  pinMode(back_buzzer_pin, OUTPUT);
  pinMode(magnetic_open_valve, OUTPUT);
  Serial.print("Connecting to controler");
  while (!PS4.isConnected()) {
    Serial.print(".");
    delay(100);
  }
  servoMotor1.attach(servo_pin1);  // attaches the servo on ESP32 pin
  servoMotor2.attach(servo_pin2);  // attaches the servo on ESP32 pin
}

byte disconnect_counter = 0;  //接続切れが2.5秒続けば非常停止モードへ
void loop() {
  if (PS4.isConnected()) {
    disconnect_counter = 0;
    int LY = PS4.LStickY() / 16;  //-8~8に変換
    int LX = PS4.LStickX() / 16;
    int RX = PS4.RStickX() / 16;
    emergency_check(PS4.L3(), PS4.Square());  //手動緊急停止プログラム
    shot(PS4.Circle());
    toggle_shutter(PS4.Cross());
    back_buzzer(LY < 0);
    motor_control(LY, LX, RX);  //オムニホイール制御
    // send_Serial2();  //Nucleoに信号を送る
  } else {  //コントローラーとの通信が2.5s以上途切れた場合、緊急停止
    disconnect_counter++;
    if (disconnect_counter >= 250) emergency_check(1, 1);  //緊急停止プログラム
    delay(9);
  }
  delay(1);
}