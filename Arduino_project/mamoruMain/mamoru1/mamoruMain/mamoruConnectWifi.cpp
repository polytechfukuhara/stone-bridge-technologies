#include<M5StickCPlus.h>
#include <WiFiClientSecure.h>

//使用自作クラス
#include"mamoruConnectWifi.h"

//インスタンス
WiFiClientSecure client; // https接続

//初期設定
void mamoruConnectWifi::init() {
  //センサーの接続
  pinMode(ADC_PIN, INPUT);
  gpio_pulldown_dis(GPIO_NUM_25); // Disable pull-down on GPIO.
  gpio_pullup_dis(GPIO_NUM_25); // Disable pull-up on GPIO.

  pinMode(GPIO_NUM_36, INPUT_PULLUP); // PIR
  pinMode(GPIO_NUM_10, OUTPUT); // 内蔵LED

  // Wi-Fiの接続
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    M5.Lcd.print('.');
    delay(500);
  }
  M5.Lcd.print("\r\nWi-Fi connected\r\nIP address: ");
  M5.Lcd.println(WiFi.localIP());
  delay(2000);
}

// LINE Notify処理関数
void mamoruConnectWifi::Line_notify(String msg) {
  client.setInsecure();
  if (!client.connect(host, 443)) {
    delay(2000);
    return;
  }
  String query = String("message=") + msg;
  String request = String("") +
                   "POST /api/notify HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" +
                   "Authorization: Bearer " + token + "\r\n" +
                   "Content-Length: " + String(query.length()) +  "\r\n" +
                   "Content-Type: application/x-www-form-urlencoded\r\n\r\n" +
                   query + "\r\n";
  client.print(request);
  delay(2000);
}

//振動センサーを送信可能
void mamoruConnectWifi::SensorSendOn() {
  if (M5.BtnA.wasPressed()) {
    if (!isActive) {
      isActive = true ;
      M5.Lcd.print("active");
    }
  }
}

//Lineへの通知(Brainで引数で振動のvoltを受け取る)
void mamoruConnectWifi::WifiSendToLine(float volt) {
  //通知
  if (volt < 0.5) {
    if (isActive) {
      Line_notify("人を検出しました！");
    }
  } else {
    volt = 3.3;
  }
}
