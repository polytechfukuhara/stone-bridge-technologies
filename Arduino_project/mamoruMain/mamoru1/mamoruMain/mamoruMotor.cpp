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

boolean mamoruMotor::getLockState(){
  if(lock_read_num == 1){ //施錠の場合
    lockFlg =true;
  }else{ //開錠の場合
    lockFlg =false;
  }
  return lockFlg;
}
