# 🏡 Smart House Automation System

Welcome to the **Smart House System** repository! This is a comprehensive, open-source home automation project built using microcontrollers (Arduino & ESP32). The objective of this project is to create an interconnected ecosystem that elevates modern home safety, optimizes energy efficiency, and automates daily tasks for maximum convenience.

---

## 🌟 Key Features & Highlights

* **🌤️ All-Weather Protection:** Automatic climate and weather response systems to safeguard home interiors.
* **⚡ Energy Efficiency:** Smart monitoring of HVAC systems to minimize power wastage.
* **🛡️ Multi-Layered Security:** Motion detection, obstacle tracking, and automated perimeter locking.
* **💨 Healthy Indoor Air:** Continuous indoor air quality analysis and automated ventilation.
* **📶 IoT Connectivity:** Remote monitoring and manual override controls via a smartphone interface.
* **🧩 Modular Architecture:** Easily extensible structure allowing seamless addition of new modules over time.

---

## 🧩 System Modules & Detailed Functionality

### 1. 🪟 Smart Window & Clothesline System
* **Module Path:** `/01-Smart-Window-System`
* **Status:** 🟢 Completed
* **Function:** Protects indoor areas and drying clothes from sudden rainstorms. A water/rain sensor continuously monitors precipitation levels. When rain is detected, a servo motor retracts the clothesline indoors or closes the window smoothly. Dual LEDs provide real-time visual feedback (Green = Safe/Dry, Red = Rain Alert).

---

### 2. 🌬️ Indoor Air Quality & Automated Ventilation
* **Module Path:** `/02-Air-Quality-Ventilation`
* **Status:** 🟡 In Development
* **Function:**
  Monitors indoor air purity and dangerous gas leaks (such as LPG, smoke, or excessive CO2) using an MQ-135 sensor. If contamination passes safety thresholds, the system automatically opens ventilation windows and activates exhaust fans to refresh room air.

---

### 3. ❄️ HVAC & Energy Preservation Module
* **Module Path:** `/03-AC-Energy-Saver`
* **Status:** 🟡 Planned
* **Function:**
  Designed to prevent energy waste during air conditioner operation. It utilizes temperature sensors (DHT11) and limit switches. If an external window is opened while the AC is active, the system alerts occupants via an audible buzzer and automatically pauses cooling until sealed.

---

### 4. ☀️ Ambient Light & Automatic Sun Blinds
* **Module Path:** `/04-Light-Sensing-Blinds`
* **Status:** 🟡 Planned
* **Function:**
  Automates natural lighting inside the house using Light Dependent Resistors (LDRs). At dawn, the system opens window blinds to allow daylight inside. At sunset, it retracts them to maintain indoor privacy and conserve night heating.

---

### 5. 🛡️ Intruder & Proximity Security Alarm
* **Module Path:** `/05-Security-Proximity-Alarm`
* **Status:** 🟡 Planned
* **Function:**
  Monitors window perimeter and doorways using Ultrasonic (HC-SR04) and PIR motion sensors. If an unauthorized approach is detected within a designated security zone during night mode, the system locks access points, turns on flashers, and triggers an alarm buzzer.

---

### 6. 📱 IoT Central Hub (ESP32 Integration)
* **Module Path:** `/06-IoT-Central-Hub`
* **Status:** 🟡 Planned
* **Function:**
  Serves as the main communication bridge connecting all local sub-systems to the internet via Wi-Fi. It pushes real-time telemetry (temperature, rain status, air quality) to a mobile application (Blynk/Telegram) and allows full manual control over any motor or switch remotely.

---

## 🛠️ Hardware Components

| Category | Component Name |
| :--- | :--- |
| **Microcontrollers** | Arduino Uno, ESP32 / ESP8266 |
| **Sensors** | Rain Sensor, MQ-135 Air Quality, LDR, DHT11 Temp/Humidity, HC-SR04 Ultrasonic |
| **Actuators** | Servo Motors, Relays, Buzzers |
| **Indicators** | Green & Red LEDs, 16x2 I2C LCD Display |

---

## 🚀 How to Explore This Repository

1. Open any module directory (e.g., `01-Smart-Window-System`) to find dedicated code files (`.ino`).
2. Read the specific `README.md` inside each folder for pinout diagrams, schematic illustrations, and setup steps.
