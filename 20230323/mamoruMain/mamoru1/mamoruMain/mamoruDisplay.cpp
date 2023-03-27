#include<M5StickCPlus.h>
#include "BluetoothSerial.h"

//使用自作クラス
#include"mamoruDisplay.h"
#include"mamoruBattery.h"
#include"mamoruBluetooth.h"
#include"mamoruConnectWifi.h"

//インスタンス
BluetoothSerial SerialBT1;
mamoruBluetooth bthDISP;
mamoruBattery batteryDISP;
mamoruConnectWifi wifiDisp;

/**
   初期設定
*/
void mamoruDisplay::Battery_Display() {
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
void mamoruDisplay::setPosAndSize(int posX, int posY, int showSizeNum) {
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
void mamoruDisplay::batteryUpdate(int percent = -1) {
  if (!_showFlg) {
    return;
  }
  // 電池図形内部背景塗りつぶし
  dispAllClean();
  // 実際にバッテリーの値を計算するか判定
  i_percent = percent;
  if (i_percent == -1) {
    i_percent = batteryDISP.calcBatteryPercent();
  }
  //****************ninomiya tuika**********4gyou******
  int b_width = int((_width-2) * (i_percent/100.0f));
  _sprite.fillRect(0, 0, b_width+1, _height-1, getBatteryColor());
  showBatteryPercent(i_percent); // バッテリー数値を表示
  _sprite.pushSprite(_x+1, _y+1); // ディスプレイに表示
  //****************ninomiya tuika**********4gyou******
}
/**
   削除時の背景色を設定する関数
*/
void mamoruDisplay::setDeleteBgColor(uint32_t color) {
  _bg_color  = color;
}
/**
   電池図形と文字の色を設定する関数
*/
void mamoruDisplay::setTextColor(uint32_t color) {
  _line_color = color;
  _text_color = color;
}
/**
   電池残量を表示する関数
*/
void mamoruDisplay::showBattery() {
  _showFlg = true;
  drawBatteryLines();
  _sprite.setColorDepth(16);
  _sprite.createSprite(_width - 1, _height - 1);
}
/**
   電池残量を非表示(塗りつぶし)する関数
*/
void mamoruDisplay::deleteBattery() {
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
void mamoruDisplay::drawBatteryLines() {
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
void mamoruDisplay::showBatteryPercent(int i_percent) {
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
uint32_t mamoruDisplay::getBatteryColor() {
  // バッテリー稼働中は緑、電圧が低い時は赤色、充電中は青色
  uint32_t color = TFT_DARKGREEN;
  if (batteryDISP.isLowBattery()) {
    color = TFT_RED;
  } else if (!batteryDISP.isUsingBattery()) {
    color = TFT_BLUE;
  }
  return color;
}

/**
   main
*/
void mamoruDisplay::batteryShow_Setup() {

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

// 電池図形内部背景塗りつぶし
void mamoruDisplay::dispAllClean() {
  _sprite.fillRect(0, 0, _width - 1, _height - 1, TFT_BLACK);
}

/**
   振動検知画面表示するを関数
*/
void mamoruDisplay::showEmergencyMove() {
  M5.Lcd.print("振動がありました");
  delay(1000);
}

/**
   Bluetooth関連
*/
//Bluetooth接続画面
void mamoruDisplay::BluetoothSearching() {
  // LCD表示設定
  M5.Lcd.setTextFont(2);
  // Bluetooth接続開始
  SerialBT1.begin(master_name, true);  // マスターとして初期化。trueを書くとマスター、省略かfalseを指定でスレーブ
  M5.Lcd.print("BT Try!\n.");
  Serial.print("BT Try!\n.");
  while (connected == 0) {    // connectedが0(未接続)なら接続実行を繰り返す
    if (connect_count != 0) { // 再接続実行回数カウントが0でなければ
      connected = SerialBT1.connect(slave_name); // 接続実行（接続名で接続する場合）
      M5.Lcd.print(".");
      connect_count--;        // 再接続実行回数カウント -1 
    } else {                  // 再接続実行回数カウントが0なら接続失敗
      M5.Lcd.setTextColor(RED, BLACK);
      M5.Lcd.print("\nFailed!");
      Serial.print("\nFailed!");
      while (1) {
        ESP.restart(); // 無限ループ(再起動待機)
      }
    }
  }
  // 接続確認
  M5.Lcd.setTextColor(WHITE, BLACK);
  if (connected) {                    // 接続成功なら
    M5.Lcd.setTextColor(CYAN, BLACK);
    M5.Lcd.println("\nConnected!");   // 「Connected!」表示
    Serial.println("\nConnected!");
    SerialBT1.print("BT:Connected!\r");
  } else {                            // 接続失敗なら
    M5.Lcd.setTextColor(RED, BLACK);
    M5.Lcd.println("\nFailed!!");     // 「Failed!!」表示
    Serial.println("\nFailed!!");
    while (1) {
      ESP.restart(); // 無限ループ(再起動待機)
    }
  }
  delay(1000);                        // 接続結果確認画面表示時間

  bthDISP.SerialDataRead(); // 電源ON時のシリアルデータが無くなるまで待つ

  // LCD表示リセット
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.println(master_name);        // 接続名表示


}
