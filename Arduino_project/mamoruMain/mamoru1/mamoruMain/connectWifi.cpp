#include<M5StickCPlus.h>
#include<ESP32Servo.h>
#include <WiFiClientSecure.h>
#include <Arduino.h>
#include "BluetoothSerial.h"
#include "esp32-hal-ledc.h"

//使用自作クラス
/*#include"Timer.h"
#include"mamoruMain.h"
#include"Display.h"
#include"Motor.h"
#include"Servo_Motor.h"
#include"Sensor.h"
#include"Battery.h"
#include"Blutooth.h"
#include"connectWifi.h"
#include"Sleep_mode.h"*/

//インスタンス化

//初期設定
void connectWifi::init() {
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
void connectWifi::Line_notify(String msg) {
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
void connectWifi::SensorSendOn() {
  if (M5.BtnA.wasPressed()) {
    if (!isActive) {
      isActive = true ;
      M5.Lcd.print("active");
    }
  }
}

//Lineへの通知(Brainで引数で振動のvoltを受け取る)
void connectWifi::WifiSendToLine(float volt) {
  //通知
  if (volt < 0.5) {
    if (isActive) {
      Line_notify("人を検出しました！");
    }
  } else {
    volt = 3.3;
  }
}
