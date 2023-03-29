#pragma once

//********************
//MAMORU Main mamoruDisplay.h
//********************

class mamoruDisplay
{
  private:
    String slave_name = "BT_Slave";   // スレーブ側の接続名
    String master_name = "BT_master"; // マスターの接続名
    bool connected = 0;       // 接続状態格納用
    int connect_count = 10;    // 再接続実行回数
    const int8_t BITS_PER_PIXEL     = 1;
    const int TRANS_PARENTS         = 0;
    const int MAX_SHOW_SIZE         = 7;
    const int MIN_SHOW_SIZE         = 1;
    TFT_eSprite _sprite = TFT_eSprite(&M5.Lcd);
    bool _showFlg;
    int i_percent;
    int _x;
    int _y;
    int _showSize;
    int _width;
    int _height;
    int _top_width;
    uint32_t _bg_color;
    uint32_t _line_color;
    uint32_t _text_color;
    void drawBatteryLines();

    int moveCount;

  public:
    uint32_t getBatteryColor();
    void showBatteryPercent(int i_percent);
    void pairingDisp(int batteryState, boolean doorLockState);
    void normalDisp(int batteryState, boolean doorLockState, boolean blutoothState);
    void emergentDisp();
    void deleteDisp();
    void startDisp();
    void Battery_Display();
    void setPosAndSize(int posX, int posY, int showSizeNum);
    void setDeleteBgColor(uint32_t color);
    void setTextColor(uint32_t color);
    void showBattery();
    void deleteBattery();
    void dispAllClean();
    void batteryShow_Setup();
    void batteryUpdate(int percent);
    void showEmergencyMove();

    void BluetoothSearching();
};
