#pragma once

class Motor
{
  private:
    boolean lockFlg;
    int lock_read_num = 0;

  public:
    void lock_door();
    void open_door();
    boolean getLockState();
};
