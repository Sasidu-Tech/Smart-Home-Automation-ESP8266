```cpp
# 🏠 ESP8266 Based Smart Room Automation System

An IoT-based Smart Room Automation system built using the **ESP8266 (NodeMCU)** microcontroller.  
It monitors environmental conditions, displays real-time data, and controls home appliances using relays.

---

## 🚀 Features

- 🌡️ **Real-time Environment Monitoring**  
  Measures temperature and humidity using the DHT11 sensor.

- ⏰ **Accurate Time Tracking**  
  Uses DS3231/DS1307 RTC module for real-time clock functionality.

- 📟 **Live LCD Display**  
  Shows temperature, humidity, and current time on a 16x2 I2C LCD.

- 🔌 **Smart Appliance Control**  
  Controls up to 4 appliances using a 4-channel relay module.

- ⚡ **Stable Power System**  
  Uses a breadboard power supply module to ensure stable operation.

---

## 🛠️ Components Used

| Component | Description |
|----------|-------------|
| NodeMCU ESP8266 | Main Wi-Fi microcontroller |
| DHT11 Sensor | Temperature & humidity sensor |
| DS3231 / DS1307 RTC | Real-time clock module |
| 16x2 I2C LCD | Display unit |
| 4-Channel Relay Module | Appliance control |
| Breadboard Power Module | Stable 5V/3.3V supply |
| Jumper Wires & Breadboard | Circuit connections |

---

## 🔌 Wiring Diagram (Basic Connections)

- **DHT11**
  - VCC → 3.3V
  - GND → GND
  - DATA → D4

- **I2C LCD + RTC Module**
  - VCC → 5V
  - GND → GND
  - SDA → D2 (GPIO4)
  - SCL → D1 (GPIO5)

- **4-Channel Relay Module**
  - VCC → 5V
  - GND → GND
  - IN1 → D5
  - IN2 → D6
  - IN3 → D7
  - IN4 → D8

---

## 💻 Required Libraries

Install the following libraries in Arduino IDE:

- DHT sensor library (Adafruit)
- LiquidCrystal_I2C
- RTClib (Adafruit)

---

## ⚙️ Setup Instructions

1. Clone the repository:
   ```bash
   git clone https://github.com/Sasidu-Tech/Smart-Home-Automation-ESP8266.git
Author : Sasidu Wishshanka
```

