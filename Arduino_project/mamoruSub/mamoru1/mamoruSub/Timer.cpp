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
Sleep_mode sleep_mode;

void Timer::init() {
  timer = timerBegin(0, getApbFrequency() / 1000000, true);
  //timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);
}

void Timer::onTimer() {
  isrCounter++;
  if (isrCounter == 180) {
    timerEnd(timer);
    timer = NULL;
    isrCounter = 0;
    
    sleep_mode.SleepStart(0, 20); //スリープ設定
  }
  /*else if (MAIN_BUTTON_PIN == HIGH) {
    timerEnd(timer);
    timer = NULL;
    isrCounter = 0;
  }*/
}
