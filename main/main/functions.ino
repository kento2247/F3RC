//緊急停止
void emergency_check(bool button, bool guard_button) {
  digitalWrite(emergency_stop, HIGH);
  if (guard_button) {  //誤操作防止ロックを解除
    //スピーカーから警告音
    if (button) {  //ジョイスティック押し込み
      //緊急停止処理
      digitalWrite(emergency_stop, LOW); //PinをGNDに短絡させる
      while (1) {
        Serial.println("emergency");
        delay(100);
      }
    }
  }
}

void shot() {
  //ロボットを自動で対面角度にする
  //ボール格納庫を開ける
  //電磁弁を開ける
  //電磁弁を閉める
}

byte send_data[Serial_data_length];
byte encoded_data[Serial_data_length + 2];
void send_Serial2() {
  reload_controler_data();
  cobs_encode();
  Serial2.write((byte*)encoded_data, sizeof(encoded_data));
}

//COBS形式でSerial通信をエンコード
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

//Nucleoに送るデータを配列に格納
void reload_controler_data() {
  send_data[0] = PS4.Circle();
  send_data[1] = PS4.Cross();
  send_data[2] = PS4.Triangle();
  //  send_data[3] = PS4.Square();

  //  send_data[4] = PS4.LStickY();
  //  send_data[5] = PS4.LStickX();
  //  send_data[6] = PS4.RStickY();
  //  send_data[7] = PS4.RStickX();
}
