#include<M5StickCPlus.h>

//使用自作クラス
#include"mamoruTimer.h"
#include"mamoruMain.h"
#include"mamoruDisplay.h"
#include"mamoruMotor.h"
#include"mamoruServo_Motor.h"
#include"mamoruSensor.h"
#include"mamoruBattery.h"
#include"mamoruBluetooth.h"
#include"mamoruConnectWifi.h"
#include"mamoruSleep_mode.h"

//インスタンス
mamoruBattery batteryMain ;
mamoruBluetooth bthMain;
mamoruDisplay dispMain;
mamoruMotor motorMain;
mamoruSensor sensorMain;
mamoruServo_Motor servoMain;
mamoruSleep_mode sleep_modeMain;
mamoruTimer timerMain;
mamoruConnectWifi wifiMain;

void setup() {
  M5.begin();
  Serial.println("System Start");
  bthMain.init();
  sensorMain.init();
  servoMain.init();
  timerMain.init();
  wifiMain.init();
}

void loop() {
  M5.update();

  int batteryAmount = batteryMain.calcBatteryPercent(); //バッテリーの残量を調べる

  if (batteryAmount > 10) { //10％以上なら
    bthMain.restart();    // 再起動（リスタート）処理
    bthMain.SerialBTSearching();    //SerialBTの読み取り
    bthMain.SerialDataRead(); //Serialデータの読み取り
    wifiMain.SensorSendOn(); //振動センサーを送信可能
    dispMain.batteryShow_Setup(); //バッテリー表示

    boolean doorFlg = motorMain.getLockState(); //ドアの開閉状態を取得
    if (doorFlg == true) {
      bthMain.BluetoothDoorOpen();    //ドアオープン
    } else {
      bthMain.BluetoothDoorcloseRestart();    //ドアロック＆本体初期化
      float moveVolt = sensorMain.sensorDetection(); //センサーの動きを検知
      if (moveVolt < 0.5) {
        wifiMain.WifiSendToLine(moveVolt); //振動をWi-FiでLINEに送信
        dispMain.showEmergencyMove(); //振動を画面表示
      }
    }
  } else { //10％以下なら
    motorMain.open_door(); //ドアオープン
    sleep_modeMain.SleepStart(0, 10); //スリープモード（低電圧）

  }
  //timerMain.onTimer(); //180秒カウント＆スリープ
}
