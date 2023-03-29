#include<M5StickCPlus.h>

//********************
//MAMORU Sub mamoruSubSleep_mode.cpp
//********************

//使用自作クラス
#include"mamoruSubSleep_mode.h"

//スリープモード関数
void mamoruSubSleep_mode::SleepStart(int timeSleep, int frequency){
  M5.Axp.ScreenBreath(timeSleep);
  setCpuFrequencyMhz(frequency);
}
