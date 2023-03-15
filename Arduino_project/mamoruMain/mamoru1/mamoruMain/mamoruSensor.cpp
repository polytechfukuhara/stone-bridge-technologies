#include<M5StickCPlus.h>

//使用自作クラス
#include"mamoruSensor.h"

void mamoruSensor::init() {
  pinMode(ADC_PIN, INPUT);
  gpio_pulldown_dis(GPIO_NUM_25); // Disable pull-down on GPIO.
  gpio_pullup_dis(GPIO_NUM_25); // Disable pull-up on GPIO.
}

float mamoruSensor::sensorDetection() {
  int val = analogRead(ADC_PIN);  // read the input pin
  float volt = Vref * float(val) / 4095.0; // 12bit
  Serial.println(volt);
  return volt;
}
