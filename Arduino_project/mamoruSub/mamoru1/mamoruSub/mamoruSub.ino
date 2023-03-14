#include<M5StickCPlus.h>

#include<ESP32Servo.h>
#include <Arduino.h>
#include "BluetoothSerial.h"

//使用自作クラス
#include"Timer.h"
#include"mamoruSub.h"
#include"Display.h"
#include"Battery.h"
#include"Blutooth.h"
#include"Sleep_mode.h"

//インスタンス
Battery battery;
Blutooth bth;
Display disp;
Timer timer;


void setup() {
  M5.begin();
  Serial.println("System Start");
  bth.init();
  timer.init();
}

void loop() {
  bth.restart();    // 再起動（リスタート）処理
  bth.BluetoothButtonPush(); //ボタン操作時の操作
  bth.SerialBTSearching(); //SerialBTの読み取り(new)
  bth.BluetoothSerialSend(); // シリアル入力データ（「CR」付きで入力）をスレーブ側へ送信
  bth.BluetoothMainButtonPush(); //本体側のボタンプッシュ後処理
  disp.batteryShow_Setup(); //バッテリー表示

  timer.onTimer(); //180秒カウント＆スリープ
}
