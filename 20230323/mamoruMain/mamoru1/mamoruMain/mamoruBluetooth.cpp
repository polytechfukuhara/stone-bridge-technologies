// Bluetooth接続マスター側プログラム

//********************
//MAMORU Main mamoruBluetooth.cpp
//********************

#include<M5StickCPlus.h>
#include "BluetoothSerial.h"

//使用自作クラス
#include"mamoruDisplay.h"
#include"mamoruMotor.h"
#include"mamoruBattery.h"
#include"mamoruBluetooth.h"

//インスタンス
BluetoothSerial SerialBT;
mamoruDisplay dispBTH;
mamoruMotor servoMoveBTH;

//初期化設定
void mamoruBluetooth::init() {
  Serial.begin(9600);     // シリアル通信初期化
  // 出力設定
  pinMode(10, OUTPUT);    //本体LED赤
  digitalWrite(10, HIGH); //本体LED初期値OFF（HIGH）

  dispBTH.BluetoothSearching(); //Buluetooth接続画面
}

// 再起動（リスタート）処理
void mamoruBluetooth::restart() {
  // 電源ボタン状態取得（1秒以下のONで「2」1秒以上で「1」すぐに「0」に戻る）
  btn_pw = M5.Axp.GetBtnPress();
  delay(20);  // 20ms遅延時間
  if (btn_pw == 2) {  // 電源ボタン短押し（1秒以下）なら
    ESP.restart();    // 再起動
  }
}

//SerialBTの読み取り(new)
void mamoruBluetooth::SerialBTSearching() {
  if (SerialBT.available()) {               // Bluetoothデータ受信で
    data = SerialBT.readStringUntil('\r');
  }
}

//Serialデータの読み取り(new)
void mamoruBluetooth::SerialDataRead() {
  // 電源ON時のシリアルデータが無くなるまで待つ
  while (Serial.available()) {
    data = Serial.read();
  }
}

//ドアロック＆本体初期化(new)
void mamoruBluetooth::BluetoothDoorcloseRestart() {
  // LED点灯処理
  if (data == "A ON!") {      // 受信データが「A ON!」なら
    servoMoveBTH.lock_door(); //ドアの施錠
    flg = servoMoveBTH.getLockState(); //ドアの状態
    if (flg == 2) {
      digitalWrite(10, LOW);  // 本体LED点灯
      SerialBT.print("Door:ROCK\r");
      delay(10);
      data = "";
      //restart
      ESP.restart(); //SubがAボタンを押した時にリスタート
    }
  }
}

//ドアオープン(new)
void mamoruBluetooth::BluetoothDoorOpen() {
  if (data == "B ON!") {      // 受信データが「B ON!」なら
    servoMoveBTH.open_door(); //ドアの施錠
    flg = servoMoveBTH.getLockState(); //ドアの状態
    if (flg == 1) {
      SerialBT.print("Door:OPEN\r");
      digitalWrite(10, HIGH);   // 本体LED消灯
      data = "";
    }
  }
}
