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
Display disp;

  /**
     バッテリー残量%を計算する関数(戻り値は0～100)
  */
  int Battery::calcBatteryPercent() {
    float _vbat = M5.Axp.GetBatVoltage();
    float percent = (_vbat - MIN_BATTERY_VOLTAGE) / (MAX_BATTERY_VOLTAGE - MIN_BATTERY_VOLTAGE);
    return roundf(percent * 100.0f);
  }
  /**
     低電圧状態かを判定する関数
  */
  bool Battery::isLowBattery() {
    // 低電圧状態(3.4V以下)だと1それ以外は0
    uint8_t _low_bat = M5.Axp.GetWarningLeve();
    if (_low_bat == 0) {
      return false;
    } else {
      return true;
    }
  }
  /**
     バッテリー稼働か充電中かを判定する関数
  */
  bool Battery::isUsingBattery() {
    // プラスが充電、マイナスがバッテリー稼働
    float _ibat = M5.Axp.GetBatCurrent();
    if (_ibat < 0.0f) {
      return true;
    } else {
      return false;
    }
  }
