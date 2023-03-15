#pragma once

class mamoruSensor
{
  private:
    const float Vref = 3.3;
    const int ADC_PIN = GPIO_NUM_33;
  public:
    void init();
    float sensorDetection();
};
