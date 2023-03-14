#include <M5StickCPlus.h>
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


//初期設定
void Servo_Motor::init(){
  ledcSetup(1, 50, TIMER_WIDTH);
  ledcAttachPin(26, 1);
}

//DoorOpen
int Servo_Motor::openKey(){
  for (int i = COUNT_LOW; i < COUNT_HIGH; i = i + 100) {
    ledcWrite(1, i);
    delay(50);
  }
  lockFlg = 0;  // 開錠時は0
}

//DoorClose
int Servo_Motor::closeKey(){
  for (int i = COUNT_HIGH; i > COUNT_LOW; i = i - 100) {
    ledcWrite(1, i);
    delay(50);
  }
  lockFlg = 1;  // 施錠時は1
}
