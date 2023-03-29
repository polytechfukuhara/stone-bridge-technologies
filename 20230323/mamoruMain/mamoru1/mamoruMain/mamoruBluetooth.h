#pragma once

//********************
//MAMORU Main mamoruBluetooth.h
//********************

class mamoruBluetooth
{
  private:
    String slave_name = "BT_Slave";   // スレーブ側の接続名
    String master_name = "BT_master"; // マスターの接続名
    bool connected = 0;       // 接続状態格納用
    String data = "";         // 受信データ格納用
    int btn_pw = 0;           // 電源ボタン状態取得用
    int flg; //Doorの状態

  public:
    void init();
    void restart();    // 再起動（リスタート）処理
    void SerialBTSearching();    //SerialBTの読み取り
    void SerialDataRead(); //Serialデータの読み取り
    void BluetoothDoorcloseRestart();    //ドアロック＆本体初期化
    void BluetoothDoorOpen();    //ドアオープン(new)
};
