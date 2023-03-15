#include <M5StickCPlus.h>
#include<ESP32Servo.h>
#include "esp32-hal-ledc.h"

//使用自作クラス
#include"mamoruServo_Motor.h"

//初期設定
void mamoruServo_Motor::init(){
  ledcSetup(1, 50, TIMER_WIDTH);
  ledcAttachPin(26, 1);
}

//DoorOpen
int mamoruServo_Motor::openKey(){
  for (int i = COUNT_LOW; i < COUNT_HIGH; i = i + 100) {
    ledcWrite(1, i);
    delay(50);
  }
  lockFlg = 0;  // 開錠時は0
  return lockFlg;
}

//DoorClose
int mamoruServo_Motor::closeKey(){
  for (int i = COUNT_HIGH; i > COUNT_LOW; i = i - 100) {
    ledcWrite(1, i);
    delay(50);
  }
  lockFlg = 1;  // 施錠時は1
  return lockFlg;
}
