#include <PS4Controller.h>

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  PS4.begin("24:62:AB:FB:15:1A");
  Serial.println("Ready.");
}

void loop() {
  // Below has all accessible outputs from the controller
  if (PS4.isConnected()) {
    if (PS4.Down()) {
      Serial.println("Down Button");
      Serial.println();
      Serial2.write(1);
    }
    else if (PS4.Up()) {
      Serial.println("Up Button");
      Serial.println();
      Serial2.write(2);
    }
    else {
      Serial2.write(0);
    }
    delay(100);
  }
}
