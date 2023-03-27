#include <M5StickCPlus.h>
#include<ESP32Servo.h>
#include "esp32-hal-ledc.h"

//使用自作クラス
#include"mamoruServo_Motor.h"

//初期設定
void mamoruServo_Motor::init() {
  ledcSetup(1, 50, TIMER_WIDTH);
  ledcAttachPin(26, 1);
}

//DoorOpen
int mamoruServo_Motor::openKey() {
  //******moto**************************************
  //for (int i = COUNT_LOW; i < COUNT_HIGH; i = i + 100) {
  //  ledcWrite(1, i);
  //  delay(50);
  //}
  //*********************************************
  //*****NEW***********************************
  for (int i = COUNT_HIGH; i > COUNT_LOW; i = i - 100) {
    ledcWrite(1, i);
    delay(50);
  }
  //*********************************************
  lockFlg = 1;
  return lockFlg;
}

//DoorClose
int mamoruServo_Motor::closeKey() {
  //******moto**************************************
  //for (int i = COUNT_HIGH; i > COUNT_LOW; i = i - 100) {
  //  ledcWrite(1, i);
  //  delay(50);
  //}
  //******moto**************************************
  //******NEW irekae**************************************
  for (int i = COUNT_LOW; i < COUNT_HIGH; i = i + 100) {
    ledcWrite(1, i);
    delay(50);
  }
  //*********************************************




  lockFlg = 2;
  return lockFlg;
}
