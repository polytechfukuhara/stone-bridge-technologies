#pragma once

//********************
//MAMORU Main mamoruMotor.h
//********************


class mamoruMotor
{
  private:
    boolean lockFlg;
    volatile int lock_read_num = 0;

  public:
    void lock_door();
    void open_door();
    int getLockState();
};
