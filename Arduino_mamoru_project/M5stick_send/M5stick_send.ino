#include <M5StickCPlus.h>
#include <WiFiClientSecure.h>

// センサー環境
const float Vref = 3.3;
const int ADC_PIN = GPIO_NUM_33;

// Wi-Fi環境
const char* ssid = "Galaxy_5GMW_4643";
const char* password = "kenta7766";

// Line Notify環境
const char* host = "notify-api.line.me";
const char* token = "L8P9tTak7BOlFINCUmZYsV2jWuGWpeRDux1XgWXowBH"; // トークン

WiFiClientSecure client; // https接続

bool isActive = false ; // trueの時だけ通知する

// LINE Notify処理関数
void Line_notify(String msg) {
  client.setInsecure();
  if (!client.connect(host, 443)) {
    delay(2000);
    //M5.Lcd.print("Line Notify disconnect");
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

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.println("PIR LINE Notify");

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

void loop() {
  // put your main code here, to run repeatedly:
  M5.update();

  if (M5.BtnA.wasPressed()) {
    String msg = "振動を検知しました";
    Line_notify(msg);
  }
  
/*
  //センサー
  int val = analogRead(ADC_PIN);  // read the input pin
  float volt = Vref * float(val) / 4095.0; // 12bit

  if (M5.BtnA.wasPressed()) {
    if (!isActive) {
      isActive = true ;
      M5.Lcd.print("active");
    }
  }

  //通知
  if (volt < 0.5) {
    if (isActive) {
      Line_notify("人を検出しました！");
    }
  } else {
    volt = 3.3;
  }*/
}
