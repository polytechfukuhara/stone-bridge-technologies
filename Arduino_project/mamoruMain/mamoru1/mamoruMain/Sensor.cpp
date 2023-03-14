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


void Sensor::init() {
  pinMode(ADC_PIN, INPUT);
  gpio_pulldown_dis(GPIO_NUM_25); // Disable pull-down on GPIO.
  gpio_pullup_dis(GPIO_NUM_25); // Disable pull-up on GPIO.
}

float Sensor::sensorDetection() {
  int val = analogRead(ADC_PIN);  // read the input pin
  float volt = Vref * float(val) / 4095.0; // 12bit
  Serial.println(volt);
  return volt;
}
