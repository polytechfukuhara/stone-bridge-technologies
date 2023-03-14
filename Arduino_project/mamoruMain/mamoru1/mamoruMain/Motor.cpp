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
Servo_Motor servo;

void Motor::open_door(){
  lock_read_num = servo.openKey();
}

void Motor::lock_door(){
  lock_read_num = servo.closeKey();
 }

boolean Motor::getLockState(){
  if(lock_read_num == 1){ //施錠の場合
    lockFlg ==true;
  }else{ //開錠の場合
    lockFlg ==false;
  }
  return lockFlg;
}
