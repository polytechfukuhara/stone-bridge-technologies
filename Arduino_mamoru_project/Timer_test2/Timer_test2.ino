#include <M5StickCPlus.h>

volatile int counter = 0;

void timerInterrupt() {
  counter++;
}
void setup() {
  M5.begin();
  Serial.begin(115200);
  timerBegin(0, 80, true);
  timerAttachInterrupt(0, &timerInterrupt, true);
  timerAlarmWrite(0, 1000000, true);
  timerAlarmEnable(0);
}
void loop() {
  M5.update();
  if (counter > 0) {
    Serial.printf("Counter: %d\n", counter);
    counter = 0;
  }
}
