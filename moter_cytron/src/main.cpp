#include "CytronMotorDriver.h"
#include "UnbufferedSerial.h"
#include "mbed.h"

#define buffer_size 64  //受け取るデータのバイト数（配列の長さ）。自由に設定可
BufferedSerial Cc(A7, A2, 115200);  //　RX,TXでのシリアルポート生成
CytronMD motor1(A6, A4);            // PWM, DIR

int main() {
  while (1) {
    if (Cc.readable()) {
      char data[buffer_size];
      Cc.read(data, buffer_size);
      printf("data=%d\n\n", data[0]);  ///今回は送信側が1byteしか送ってないから

      char dir = data[0];
      if (dir == 2) {
        motor1.speed(1);
      } else if (dir == 1) {
        motor1.speed(-1);
      } else {
        motor1.speed(0);
      }
    }
    wait_us(50000);
  }
}