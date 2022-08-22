#include <PS4Controller.h>
#define Serial_data_length 4

//pin割り当て
#define magnetic_valve 2
#define emergency_stop 15
#define pwm_1 33  //pin指定
#define pwm_2 26  //pin指定
#define pwm_3 14  //pin指定
#define pwm_4 13  //pin指定
#define dir_1 32  //pin指定
#define dir_2 25  //pin指定
#define dir_3 27  //pin指定
#define dir_4 12  //pin指定

void setup() {
  Serial.begin(115200); //デバック用
  Serial2.begin(115200);
  PS4.begin("24:62:AB:FB:15:1A");
  pinMode(magnetic_valve, OUTPUT);
  pinMode(emergency_stop, OUTPUT);
}

byte disconnect_counter = 0;
void loop() {
  if (PS4.isConnected()) {
    disconnect_counter = 0;
    emergency_check(PS4.L3(), PS4.Square()); //緊急停止プログラム
    motor_control(PS4.LStickY(), PS4.LStickX(), PS4.RStickX());  //オムニホイール制御
    send_Serial2();  //Nucleoに信号を送る
  }
  else { //コントローラーとの通信が2.5s以上途切れた場合、緊急停止
    disconnect_counter++;
    if (disconnect_counter >= 250) emergency_check(1, 1); //緊急停止プログラム
    delay(10);
  }
}
