#pragma once

//********************
//MAMORU Main mamoruConnectWifi.h
//********************

class mamoruConnectWifi
{
  private:
    bool isActive = false ; // trueの時だけ通知する
    // センサー環境
    const float Vref = 3.3;
    const int ADC_PIN = GPIO_NUM_33;
    // Wi-Fi環境
    //const char* ssid = "Galaxy_5GMW_4643";
    //const char* password = "kenta7766";

    const char* ssid = "HUAWEI Mate 20 X"; //nino
    const char* password = "hyhyhyhy";  //nino
    // Line Notify環境
    const char* host = "notify-api.line.me";
    //const char* token = "L8P9tTak7BOlFINCUmZYsV2jWuGWpeRDux1XgWXowBH"; // トークン
    const char* token = "GpAieMJarBlVGivBBYCDmHnrts3aaarNNjy0WtoVQCU"; // トークンnino

  public:
    //初期設定
    void init();
    void Line_notify(String msg);// LINE Notify処理関数
    void SensorSendOn();//振動センサーを送信可能
    void WifiSendToLine(float volt);//Lineへの通知(Brainで引数で振動のvoltを受け取る)
    void WifiSendToLineFake(); //本体のAボタンを押すとLINEに通知が飛ぶ（フェイク）
};
