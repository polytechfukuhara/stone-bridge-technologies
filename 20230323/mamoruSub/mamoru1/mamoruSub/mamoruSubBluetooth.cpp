// Bluetooth接続スレーブ側プログラム

//********************
//MAMORU Sub mamoruSubBluetooth.cpp
//********************

#include<M5StickCPlus.h>
#include "BluetoothSerial.h"

//使用自作クラス
#include"mamoruSubDisplay.h"
#include"mamoruSubBluetooth.h"

//インスタンス
BluetoothSerial SerialBT;
mamoruSubDisplay dispBTHsub;

//初期化設定
void mamoruSubBluetooth::init() {
  Serial.begin(9600);     // シリアル通信初期化
  // 出力設定
  pinMode(10, OUTPUT);    //本体LED赤
  digitalWrite(10, HIGH); //本体LED初期値OFF（HIGH）

  dispBTHsub.BluetoothSearching(); //Buluetooth接続画面
}

// 再起動（リスタート）処理
void mamoruSubBluetooth::restart() {
  // 電源ボタン状態取得（1秒以下のONで「2」1秒以上で「1」すぐに「0」に戻る）
  btn_pw = M5.Axp.GetBtnPress();
  delay(20);  // 20ms遅延時間
  if (btn_pw == 2) {  // 電源ボタン短押し（1秒以下）なら
    ESP.restart();    // 再起動
  }
}

//ボタン操作時の操作
void mamoruSubBluetooth::BluetoothButtonPush() {
  // ボタン操作処理（マスター側へデータ送信）
  if (M5.BtnA.wasPressed()) {   // ボタンAが押されていれば
    SerialBT.print("A ON!\r");  // 「A ON!」送信（「CR」区切り文字）
  }
  if (M5.BtnB.wasPressed()) {   // ボタンBが押されていれば
    SerialBT.print("B ON!\r");  // 「B ON!」送信（「CR」区切り文字）
  }
}
//SerialBTの読み取り
void mamoruSubBluetooth::SerialBTSearching() {
  if (SerialBT.available()) {               // Bluetoothデータ受信で
    data = SerialBT.readStringUntil('\r');
    M5.Lcd.println(data);                   // 液晶表示は改行あり
    Serial.print(data);                     // シリアル出力は改行なし
  }
}

// シリアル入力データ（「CR」付きで入力）をスレーブ側へ送信
void mamoruSubBluetooth::BluetoothSerialSend() {
  if (Serial.available()) {               // シリアルデータ受信で
    data = Serial.readStringUntil('\r');  // 「CR」の手前までデータ取得
    M5.Lcd.print("SR: ");                 // シリアルデータ液晶表示
    M5.Lcd.println(data);                 // 液晶表示は改行あり
    Serial.print(data);                   // シリアル出力は改行なし
    // Bluetoothデータ送信
    SerialBT.print(data + "\r"); // 区切り文字「CR」をつけてマスター側へ送信
  }
}

//本体側のボタンプッシュ後処理
void mamoruSubBluetooth::BluetoothMainButtonPush() {
  // LED点灯処理
  if (data == "A ON!") {      // 受信データが「A ON!」なら
    digitalWrite(10, LOW);    // 本体LED点灯
    data = "";
  }
  if (data == "B ON!") {      // 受信データが「B ON!」なら
    digitalWrite(10, HIGH);   // 本体LED消灯
    data = "";
  }
}

//Serialデータの読み取り(new)
void mamoruSubBluetooth::SerialDataRead() {
  // 電源ON時のシリアルデータが無くなるまで待つ
  while (Serial.available()) {
    data = Serial.read();
  }
}
