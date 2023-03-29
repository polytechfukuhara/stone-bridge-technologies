#pragma once

//********************
//MAMORU Main mamoruServo_Motor.h
//********************



#define COUNT_LOW   1500  //OPENの位置
#define COUNT_HIGH  4500  //Closeの位置4500で約90度　8500で約180度　（1500を基準として）
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
