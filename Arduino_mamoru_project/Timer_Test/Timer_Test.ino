#include<M5StickCPlus.h>

hw_timer_t * timer;
volatile uint32_t isrCounter;

int timeSleep = 0;
int frequency = 20;

void onTimer() {
  isrCounter++;
  Serial.println(isrCounter);
  if (isrCounter == 15) {
    timerEnd(timer);
    timer = NULL;
    isrCounter = 0;

    M5.Axp.ScreenBreath(timeSleep);
    setCpuFrequencyMhz(frequency);
  }
}

void setup() {
  M5.begin();
  Serial.println("System Start");

  timer = timerBegin(0, getApbFrequency() / 1000000, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);
}

void loop() {
  M5.update();  // 本体のボタン状態更新

  if (M5.BtnB.wasPressed()) {
    M5.Lcd.setTextFont(2);
    M5.Lcd.setTextColor(RED, BLACK);
    String msg = "BUTOON CLICK";
    M5.Lcd.print(msg);
    Serial.print(msg);
    isrCounter = 0;
  }
}
