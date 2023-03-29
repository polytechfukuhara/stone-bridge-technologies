#include<M5StickCPlus.h>
//********************
//MAMORU Main
//********************

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
  Serial.begin(115200);
  Serial.println("System Start");
  wifiMain.init();
  bthMain.init();
  sensorMain.init();
  servoMain.init();
  timerMain.init();
}

void loop() {
  M5.update();
  //************************
  static long i = 0 ;
  i++;
  //************************


  int batteryAmount = batteryMain.calcBatteryPercent(); //バッテリーの残量を調べる

  if (batteryAmount > 10) { //10％以上なら
    bthMain.restart();    // 再起動（リスタート）処理
    bthMain.SerialBTSearching();    //SerialBTの読み取り
    bthMain.SerialDataRead(); //Serialデータの読み取り
    wifiMain.SensorSendOn(); //振動センサーを送信可能
    dispMain.batteryShow_Setup(); //バッテリー表示

    int doorFlg = motorMain.getLockState(); //ドアの開閉状態を取得

    Serial.println(doorFlg);

    //doorFlgにうまく戻り値が入らない為、現在はdoorFlg=0のみ動き

    if (doorFlg == 0) {
      bthMain.BluetoothDoorOpen();    //ドアオープン
      bthMain.BluetoothDoorcloseRestart();    //ドアロック＆本体初期化
    }
    if (doorFlg == 2) {
      bthMain.BluetoothDoorOpen();    //ドアオープン
    } else if (doorFlg == 1) {
      bthMain.BluetoothDoorcloseRestart();    //ドアロック＆本体初期化
    }
    if (doorFlg == 2) {
      float moveVolt = sensorMain.sensorDetection(); //センサーの動きを検知
      if (moveVolt < 0.5) {
        wifiMain.WifiSendToLine(moveVolt); //振動をWi-FiでLINEに送信
        dispMain.showEmergencyMove(); //振動を画面表示
      }
    }

    //Lineへの通知（フェイク）（動かない）
    wifiMain.WifiSendToLineFake();

    //*****************************************
    //if (M5.BtnB.wasPressed()) {
    if (i == 500) {
      String msg = "振動を検知しましたB";
      wifiMain.Line_notify(msg);
      i = 0;
      //************
      //}else{
      //;}
      //***************
    }
    //*****************************************
    Serial.println(i);
    //****************

  } else { //10％以下なら
    motorMain.open_door(); //ドアオープン
    sleep_modeMain.SleepStart(0, 10); //スリープモード（低電圧）
  }
  //timerMain.onTimer(); //180秒カウント＆スリープ(コメントアウト中)
}
