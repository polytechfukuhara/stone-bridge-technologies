#include<M5StickCPlus.h>

//使用自作クラス
#include"mamoruSubTimer.h"
#include"mamoruSubDisplay.h"
#include"mamoruSubBattery.h"
#include"mamoruSubBluetooth.h"
#include"mamoruSubSleep_mode.h"

//インスタンス
mamoruSubBattery batterySub;
mamoruSubBluetooth bthSub;
mamoruSubDisplay dispSub;
mamoruSubTimer timerSub;


void setup() {
  M5.begin();
  Serial.println("System Start");
  bthSub.init();
  timerSub.init();
}

void loop() {
  bthSub.restart();    // 再起動（リスタート）処理
  bthSub.BluetoothButtonPush(); //ボタン操作時の操作
  bthSub.SerialBTSearching(); //SerialBTの読み取り(new)
  bthSub.BluetoothSerialSend(); // シリアル入力データ（「CR」付きで入力）をスレーブ側へ送信
  bthSub.BluetoothMainButtonPush(); //本体側のボタンプッシュ後処理
  dispSub.batteryShow_Setup(); //バッテリー表示

  //timerSub.onTimer(); //180秒カウント＆スリープ
}
