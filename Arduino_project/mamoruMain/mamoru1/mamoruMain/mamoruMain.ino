#include<M5StickCPlus.h>
#include<ESP32Servo.h>
#include <WiFiClientSecure.h>
#include <Arduino.h>
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
Battery battery;
Blutooth bth;
Display disp;
Motor motor;
Sensor sensor;
Servo_Motor servo;
Sleep_mode sleep_mode;
Timer timer;
connectWifi wifi;

void setup() {
  M5.begin();
  Serial.println("System Start");
  bth.init();
  sensor.init();
  servo.init();
  timer.init();
  wifi.init();
}

void loop() {
  M5.update();

  int batteryAmount = battery.calcBatteryPercent(); //バッテリーの残量を調べる

  if (batteryAmount > 10) { //10％以上なら
    bth.restart();    // 再起動（リスタート）処理
    bth.SerialBTSearching();    //SerialBTの読み取り
    bth.SerialDataRead(); //Serialデータの読み取り
    wifi.SensorSendOn(); //振動センサーを送信可能
    disp.batteryShow_Setup(); //バッテリー表示

    boolean doorFlg = motor.getLockState(); //ドアの開閉状態を取得
    if (doorFlg == true) {
      bth.BluetoothDoorOpen();    //ドアオープン
    } else {
      bth.BluetoothDoorcloseRestart();    //ドアロック＆本体初期化
      float moveVolt = sensor.sensorDetection(); //センサーの動きを検知
      if (moveVolt < 0.5) {
        wifi.WifiSendToLine(moveVolt); //振動をWi-FiでLINEに送信
        disp.showEmergencyMove(); //振動を画面表示
      }
    }
  } else { //10％以下なら
    motor.open_door(); //ドアオープン
    sleep_mode.SleepStart(0, 10); //スリープモード（低電圧）

  }
  timer.onTimer(); //180秒カウント＆スリープ
}
