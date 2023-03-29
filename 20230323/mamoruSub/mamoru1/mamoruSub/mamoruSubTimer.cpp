#include<M5StickCPlus.h>

//********************
//MAMORU Sub mamoruSubTimer.cpp
//********************

//使用自作クラス
#include"mamoruSubTimer.h"
#include"mamoruSubSleep_mode.h"

//インスタンス
mamoruSubSleep_mode sleep_modeTMsub;

void mamoruSubTimer::init() {
  timer = timerBegin(0, getApbFrequency() / 1000000, true);
  //timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);
}

void mamoruSubTimer::onTimer() {
  isrCounter++;
  if (isrCounter == 180) {
    timerEnd(timer);
    timer = NULL;
    isrCounter = 0;
    
    sleep_modeTMsub.SleepStart(0, 20); //スリープ設定
  }
  /*else if (MAIN_BUTTON_PIN == HIGH) {
    timerEnd(timer);
    timer = NULL;
    isrCounter = 0;
  }*/
}
