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

//スリープモード関数
void Sleep_mode::SleepStart(int timeSleep, int frequency){
  M5.Axp.ScreenBreath(timeSleep);
  setCpuFrequencyMhz(frequency);
}
