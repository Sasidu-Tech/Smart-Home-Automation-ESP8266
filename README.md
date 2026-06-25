-Project Image-
<img width="3968" height="2976" alt="IMG_20260625_115155_624" src="https://github.com/user-attachments/assets/d3fc79d7-87da-49b1-add9-805f35cf77b7" />
<img width="3968" height="2976" alt="IMG_20260625_115153_503" src="https://github.com/user-attachments/assets/198b2cae-c548-44af-8d61-4a1293fb7d39" />
<img width="1080" height="2460" alt="Screenshot_20260625-115511" src="https://github.com/user-attachments/assets/282e8cad-6442-49c9-b7f3-eaa3ee9d6b8d" />
<img width="1080" height="2460" alt="Screenshot_20260625-115501" src="https://github.com/user-attachments/assets/1adcf254-3494-434e-9349-523136eccece" />
<img width="1080" height="2460" alt="Screenshot_20260625-115452" src="https://github.com/user-attachments/assets/381420ce-542f-493b-a3a6-b7a070fa2baa" />
<img width="3968" height="2976" alt="IMG_20260625_115529_575" src="https://github.com/user-attachments/assets/2cae5b1e-253a-46af-990f-2db1c39cc63b" />
<img width="3968" height="2976" alt="IMG_20260625_115300_712" src="https://github.com/user-attachments/assets/f7eb4754-5a12-45cc-8ac3-1ddc2cfcee23" />
<img width="3968" height="2976" alt="IMG_20260625_115235_725" src="https://github.com/user-attachments/assets/73fe7121-5a3d-49fd-8d9f-28562f2da948" />
<img width="3968" height="2976" alt="IMG_20260625_115233_323" src="https://github.com/user-attachments/assets/43f8b36c-0492-49b7-8f23-69ce222058c4" />


##Arduino Code

```cpp
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include "RTClib.h"

// WIFI
const char* ssid = "SMART";
const char* password = "12345678";

// WEB SERVER
ESP8266WebServer server(80);

// RELAY PINS
#define R1 D0
#define R2 D6

// DHT11
#define DHTPIN D5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// RTC
RTC_DS3231 rtc;

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// DAY NAMES
const char* daysOfWeek[] = {
  "Sun", "Mon", "Tue", "Wed",
  "Thu", "Fri", "Sat"
};

void setup() {

  Serial.begin(115200);

  // RELAY SETUP
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);

  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);

  // I2C START (SDA=D2, SCL=D1)
  Wire.begin(D2, D1);

  // LCD START
  lcd.begin(16, 2);
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("ESP START");

  // DHT START
  dht.begin();

  // RTC START
  if (!rtc.begin()) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("RTC ERROR");
    while (1);
  }

  // FIRST TIME ONLY (uncomment once)
   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  delay(2000);
  lcd.clear();

  // WIFI ACCESS POINT
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  Serial.println("WiFi Started");
  Serial.println(WiFi.softAPIP());

  lcd.setCursor(0,0);
  lcd.print("WiFi Ready");
  lcd.setCursor(0,1);
  lcd.print(WiFi.softAPIP());

  delay(3000);

  // WEB ROUTES
  server.on("/", []() {
    server.send(200, "text/plain", "ESP8266 OK");
  });

  server.on("/1/on", []() {
    digitalWrite(R1, LOW);
    server.send(200, "text/plain", "Relay1 ON");
  });

  server.on("/1/off", []() {
    digitalWrite(R1, HIGH);
    server.send(200, "text/plain", "Relay1 OFF");
  });

  server.on("/2/on", []() {
    digitalWrite(R2, LOW);
    server.send(200, "text/plain", "Relay2 ON");
  });

  server.on("/2/off", []() {
    digitalWrite(R2, HIGH);
    server.send(200, "text/plain", "Relay2 OFF");
  });

  server.begin();
}

void loop() {

  server.handleClient();

  // =====================
  // TEMP + HUM DISPLAY
  // =====================
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  lcd.clear();

  if (isnan(h) || isnan(t)) {
    lcd.setCursor(0,0);
    lcd.print("DHT ERROR");
  } else {
    lcd.setCursor(0,0);
    lcd.print("Temp:");
    lcd.print(t);
    lcd.print("C");

    lcd.setCursor(0,1);
    lcd.print("Hum:");
    lcd.print(h);
    lcd.print("%");
  }

  delay(3000);

  // =====================
  // TIME + DATE DISPLAY
  // =====================
  DateTime now = rtc.now();

  lcd.clear();

  // TIME (T:)
  lcd.setCursor(0,0);
  lcd.print("T:");

  if (now.hour() < 10) lcd.print("0");
  lcd.print(now.hour());
  lcd.print(":");

  if (now.minute() < 10) lcd.print("0");
  lcd.print(now.minute());
  lcd.print(":");

  if (now.second() < 10) lcd.print("0");
  lcd.print(now.second());

  // DATE (D: YYYY/MM/DD)
  lcd.setCursor(0,1);
  lcd.print("D:");

  lcd.print(now.year());
  lcd.print("/");

  if (now.month() < 10) lcd.print("0");
  lcd.print(now.month());
  lcd.print("/");

  if (now.day() < 10) lcd.print("0");
  lcd.print(now.day());

  lcd.print(" ");
  lcd.print(daysOfWeek[now.dayOfTheWeek()]);
```

  delay(3000);
}
