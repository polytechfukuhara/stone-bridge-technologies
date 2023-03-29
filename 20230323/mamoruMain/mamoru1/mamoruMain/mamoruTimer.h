#pragma once

//********************
//MAMORU Main mamoruTimer.h
//********************

class mamoruTimer
{
  private:
  hw_timer_t * timer;
  volatile uint32_t isrCounter;
  
  public:
  void onTimer(); //タイマーを発生させるタイミングの関数をいれる
  void init();
};
