#pragma once
/**
   Batteryクラス
   電池残量を表示する。
*/
class Battery {
  private:
    const float MAX_BATTERY_VOLTAGE = 4.2f;
    const float MIN_BATTERY_VOLTAGE = 3.0f;
  public:
    int calcBatteryPercent();
    bool isLowBattery();
    bool isUsingBattery();
};
