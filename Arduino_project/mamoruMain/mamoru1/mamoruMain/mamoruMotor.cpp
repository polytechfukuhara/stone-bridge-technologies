#include<M5StickCPlus.h>

//使用自作クラス
#include"mamoruMotor.h"
#include"mamoruServo_Motor.h"

//インスタンス
mamoruServo_Motor servoMT;

void mamoruMotor::open_door(){
  lock_read_num = servoMT.openKey();
}

void mamoruMotor::lock_door(){
  lock_read_num = servoMT.closeKey();
 }

int mamoruMotor::getLockState(){
  return lock_read_num;
}
