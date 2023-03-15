#pragma once

#define COUNT_LOW   1500
#define COUNT_HIGH  8500
#define TIMER_WIDTH 16

class mamoruServo_Motor
{
  private:
  int lockFlg;
  
  public:
  void init();
  int openKey(); //DoorOpen
  int closeKey(); //DoorClose
};
