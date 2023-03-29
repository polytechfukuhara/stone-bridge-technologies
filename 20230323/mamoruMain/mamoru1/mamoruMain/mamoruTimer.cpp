#include<M5StickCPlus.h>

//********************
//MAMORU Main mamoruTimer.cpp
//********************


//使用自作クラス
#include"mamoruTimer.h"
#include"mamoruSleep_mode.h"

//インスタンス
mamoruSleep_mode sleep_modeTM;


void mamoruTimer::init() {
  timer = timerBegin(0, getApbFrequency() / 1000000, true); //一秒
  //timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);
}

void mamoruTimer::onTimer() {
  isrCounter++;
  if (isrCounter == 180) {
    timerEnd(timer);
    timer = NULL;
    isrCounter = 0;
    
    sleep_modeTM.SleepStart(0, 20); //スリープ設定
  }
  /*else if (MAIN_BUTTON_PIN == HIGH) {
    timerEnd(timer);
    timer = NULL;
    isrCounter = 0;
  }*/
}
