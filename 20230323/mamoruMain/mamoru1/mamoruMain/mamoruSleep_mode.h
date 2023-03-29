#pragma once

//********************
//MAMORU Main mamoruSleep_mode.h
//********************

class mamoruSleep_mode
{
  private:
  int timeSleep;
  int frequency;
  
  public:
  void SleepStart(int timeSleep, int frequency);
};
