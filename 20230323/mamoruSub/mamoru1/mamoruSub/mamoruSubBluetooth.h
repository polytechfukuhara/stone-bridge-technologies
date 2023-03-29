#pragma once

//********************
//MAMORU Sub mamoruSubBluetooth.h
//********************


class mamoruSubBluetooth
{
  private:
    int btn_pw = 0;           // 電源ボタン状態取得用
    String data = "";         // 受信データ格納用

  public:
    void init(); //初期化設定
    void restart(); // 再起動（リスタート）処理
    void BluetoothButtonPush(); //ボタン操作時の操作
    void SerialBTSearching(); //SerialBTの読み取り
    void SerialDataRead(); //Serialデータの読み取り
    void BluetoothSerialSend(); // シリアル入力データ（「CR」付きで入力）をスレーブ側へ送信
    void BluetoothMainButtonPush(); //本体側のボタンプッシュ後処理
};
