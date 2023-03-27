#include<M5StickCPlus.h>
#include "BluetoothSerial.h"

//使用自作クラス
#include"mamoruSubDisplay.h"
#include"mamoruSubBattery.h"
#include"mamoruSubBluetooth.h"

//インスタンス
BluetoothSerial SerialBT1;
mamoruSubBluetooth bthDISPsub;
mamoruSubBattery batteryDISPsub;

/**
   初期設定
*/
void mamoruSubDisplay::Battery_Display() {
  // 初期化
  _showFlg = true;
  _x = 0;
  _y = 0;
  _showSize = 1;
  _width     = 28 * _showSize;
  _height    = 10 * _showSize;
  _top_width =  2 * _showSize;
  _bg_color   = TFT_BLACK;
  _line_color = TFT_WHITE;
  _text_color = TFT_WHITE;
}
/**
   表示位置(x, y)と表示サイズを設定する関数
*/
void mamoruSubDisplay::setPosAndSize(int posX, int posY, int showSizeNum) {
  _x = posX;
  _y = posY;
  if (MAX_SHOW_SIZE < showSizeNum) {
    _showSize = MAX_SHOW_SIZE;
  } else if (showSizeNum < MIN_SHOW_SIZE) {
    _showSize = MIN_SHOW_SIZE;
  } else {
    _showSize  = showSizeNum;
  }
  _width     = 28 * _showSize;
  _height    = 10 * _showSize;
  _top_width =  2 * _showSize;
}

/**
   バッテリー残量の表示を更新する関数
*/
void mamoruSubDisplay::batteryUpdate(int percent = -1) {
  if (!_showFlg) {
    return;
  }
  // 電池図形内部背景塗りつぶし
  dispAllClean();
  // 実際にバッテリーの値を計算するか判定
  i_percent = percent;
  if (i_percent == -1) {
    i_percent = batteryDISPsub.calcBatteryPercent();
  }
  //****************ninomiya tuika**********4gyou******
  int b_width = int((_width - 2) * (i_percent / 100.0f));
  _sprite.fillRect(0, 0, b_width + 1, _height - 1, getBatteryColor());
  showBatteryPercent(i_percent); // バッテリー数値を表示
  _sprite.pushSprite(_x + 1, _y + 1); // ディスプレイに表示
  //****************ninomiya tuika**********4gyou******


}
/**
   削除時の背景色を設定する関数
*/
void mamoruSubDisplay::setDeleteBgColor(uint32_t color) {
  _bg_color  = color;
}
/**
   電池図形と文字の色を設定する関数
*/
void mamoruSubDisplay::setTextColor(uint32_t color) {
  _line_color = color;
  _text_color = color;
}
/**
   電池残量を表示する関数
*/
void mamoruSubDisplay::showBattery() {
  _showFlg = true;
  drawBatteryLines();
  _sprite.setColorDepth(16);
  _sprite.createSprite(_width - 1, _height - 1);
}
/**
   電池残量を非表示(塗りつぶし)する関数
*/
void mamoruSubDisplay::deleteBattery() {
  // スプライト全体を_bg_colorで塗りつぶしてメモリ開放
  _sprite.deleteSprite();
  _sprite.createSprite(_width + _top_width, _height + 1);
  _sprite.fillSprite(_bg_color);
  _sprite.pushSprite(_x, _y);
  _sprite.deleteSprite();
  _showFlg = false;
  // バッテリー残量の割合を計算して背景色塗りつぶし
  int b_width = int((_width - 2) * (i_percent / 100.0f));
  _sprite.fillRect(0, 0, b_width + 1, _height - 1, getBatteryColor());
  showBatteryPercent(i_percent); // バッテリー数値を表示
  _sprite.pushSprite(_x + 1, _y + 1); // ディスプレイに表示
}
/**
   電池の図形を作成する関数
*/
void mamoruSubDisplay::drawBatteryLines() {
  // 透明部分も作れるスプライト範囲を作成
  _sprite.setColorDepth(BITS_PER_PIXEL);
  _sprite.createSprite(_width + _top_width, _height + 1);
  _sprite.fillSprite(TRANS_PARENTS);
  // 電池図形を作成
  _sprite.fillRect(0, 0, _width + 1, _height + 1, _line_color);
  _sprite.fillRect(1, 1, _width - 1, _height - 1, TRANS_PARENTS);
  _sprite.fillRect(_width + 1, _top_width, _top_width, _height - (_top_width * 2) + 1, _line_color);
  _sprite.setBitmapColor(_line_color, TRANS_PARENTS); // 色を設定
  _sprite.pushSprite(_x, _y, TRANS_PARENTS); // 表示
  _sprite.deleteSprite(); // メモリ開放
}
/**
   バッテリー残量を表示する関数
*/
void mamoruSubDisplay::showBatteryPercent(int i_percent) {
  // バッテリー数値を表示
  _sprite.setCursor(0 + _showSize, 0 + _showSize);
  _sprite.setTextFont(1);
  _sprite.setTextColor(_text_color);
  _sprite.setTextSize(_showSize);
  _sprite.print(i_percent);
  _sprite.print("%");
}
/**
   バッテリーの状態に応じて色を取得する関数
*/
uint32_t mamoruSubDisplay::getBatteryColor() {
  // バッテリー稼働中は緑、電圧が低い時は赤色、充電中は青色
  uint32_t color = TFT_DARKGREEN;
  if (batteryDISPsub.isLowBattery()) {
    color = TFT_RED;
  } else if (!batteryDISPsub.isUsingBattery()) {
    color = TFT_BLUE;
  }
  return color;
}

/**
   main
*/


//**************************************************
void mamoruSubDisplay::batteryShow_Setup() {

  Battery_Display();
  // 表示左上の位置x, yと表示サイズ(1-7)を設定
  setPosAndSize(5, 200, 2);
  // deleteBattery()時の塗りつぶし色を設定
  setDeleteBgColor(TFT_BLACK);
  // 電池図形と%表示の色を設定
  setTextColor(TFT_WHITE);
  // バッテリーを表示
  showBattery();
  Serial.println("setup end!");
  int count = 0;
  bool showFlg = true;
  if (count > 100) {
    count = 0;
    showFlg = !showFlg;
    if (showFlg) {
      showBattery();
    } else {
      deleteBattery();
    }
  }
  // 電池の電圧から計算して表示
  batteryUpdate();
}
//**************************************************


// 電池図形内部背景塗りつぶし
void mamoruSubDisplay::dispAllClean() {
  _sprite.fillRect(0, 0, _width - 1, _height - 1, TFT_BLACK);
}

/**
   振動検知画面表示するを関数
*/
void mamoruSubDisplay::showEmergencyMove() {
  M5.Lcd.print("振動がありました");
  delay(1000);
}


/**
   Bluetooth関連
*/
//Bluetooth接続画面(new)
void mamoruSubDisplay::BluetoothSearching() {
  // LCD表示設定
  M5.Lcd.setTextFont(2);
  M5.Lcd.println(name); // 接続名表示
  // Bluetooth接続開始
  SerialBT1.begin(name); // 接続名を指定して初期化。第2引数にtrueを書くとマスター、省略かfalseでスレーブ
  // MACアドレスの取得と表示
  uint8_t macBT[6];
  esp_read_mac(macBT, ESP_MAC_BT);  // MACアドレス取得
  M5.Lcd.printf("%02X:%02X:%02X:%02X:%02X:%02X\r\n", macBT[0], macBT[1], macBT[2], macBT[3], macBT[4], macBT[5]);
  Serial.printf("%02X:%02X:%02X:%02X:%02X:%02X\r\n", macBT[0], macBT[1], macBT[2], macBT[3], macBT[4], macBT[5]);

  bthDISPsub.SerialDataRead(); // 電源ON時のシリアルデータが無くなるまで待つ

  M5.Lcd.setTextFont(4);  // テキストサイズ変更
}
