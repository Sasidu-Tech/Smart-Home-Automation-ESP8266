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
  delay(3000);
}
