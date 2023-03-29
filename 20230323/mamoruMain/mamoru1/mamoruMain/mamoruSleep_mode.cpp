#include<M5StickCPlus.h>

//********************
//MAMORU Main mamoruSleep_mode.cpp
//********************


//使用自作クラス
#include"mamoruSleep_mode.h"

//スリープモード関数
void mamoruSleep_mode::SleepStart(int timeSleep, int frequency){
  M5.Axp.ScreenBreath(timeSleep);
  setCpuFrequencyMhz(frequency);
}
