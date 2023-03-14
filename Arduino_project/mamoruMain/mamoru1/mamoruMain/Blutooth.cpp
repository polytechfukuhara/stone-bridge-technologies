// Bluetooth接続マスター側プログラム

#include<M5StickCPlus.h>
#include<ESP32Servo.h>
#include <WiFiClientSecure.h>
#include "BluetoothSerial.h"
#include "esp32-hal-ledc.h"

//使用自作クラス
#include"Timer.h"
#include"mamoruMain.h"
#include"Display.h"
#include"Motor.h"
#include"Servo_Motor.h"
#include"Sensor.h"
#include"Battery.h"
#include"Blutooth.h"
#include"connectWifi.h"
#include"Sleep_mode.h"

//インスタンス
Display disp;
Motor servoMove;

//初期化設定
void Blutooth::init() {
  Serial.begin(9600);     // シリアル通信初期化
  // 出力設定
  pinMode(10, OUTPUT);    //本体LED赤
  digitalWrite(10, HIGH); //本体LED初期値OFF（HIGH）

  disp.BluetoothSearching(); //Buluetooth接続画面
}

// 再起動（リスタート）処理
void Blutooth::restart() {
  // 電源ボタン状態取得（1秒以下のONで「2」1秒以上で「1」すぐに「0」に戻る）
  btn_pw = M5.Axp.GetBtnPress();
  delay(20);  // 20ms遅延時間
  if (btn_pw == 2) {  // 電源ボタン短押し（1秒以下）なら
    ESP.restart();    // 再起動
  }
}

//SerialBTの読み取り(new)
void Blutooth::SerialBTSearching() {
  if (SerialBT.available()) {               // Bluetoothデータ受信で
    data = SerialBT.readStringUntil('\r');
  }
}

//Serialデータの読み取り(new)
void Blutooth::SerialDataRead() {
  // 電源ON時のシリアルデータが無くなるまで待つ
  while (Serial.available()) {
    data = Serial.read();
  }
}

//ドアロック＆本体初期化(new)
void Blutooth::BluetoothDoorcloseRestart() {
  // LED点灯処理
  if (data == "A ON!") {      // 受信データが「A ON!」なら
    servoMove.lock_door(); //ドアの施錠
    flg = servoMove.getLockState(); //ドアの状態
    if (flg == true) {
      digitalWrite(10, LOW);  // 本体LED点灯
      SerialBT.print("Door:ROCK!\r");
      data = "";
      //restart
      ESP.restart(); //mainがAボタンを押した時にリスタート
    }
  }
}

//ドアオープン(new)
void Blutooth::BluetoothDoorOpen() {
  if (data == "B ON!") {      // 受信データが「B ON!」なら
    servoMove.open_door(); //ドアの施錠
    flg = servoMove.getLockState(); //ドアの状態
    if (flg == false) {
      SerialBT.print("Door:OPEN!\r");
      digitalWrite(10, HIGH);   // 本体LED消灯
      data = "";
    }
  }
}
