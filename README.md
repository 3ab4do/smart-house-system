# 🏡 Smart House System

Welcome to the **Smart House** repository! This project is an ongoing modular home automation system designed to make everyday living safer, smarter, and more convenient using Arduino and Microcontrollers.

---

## 🪟 1. Smart Window & Clothesline System
* **Status:** 🛠️ In Development

### 📝 Overview
This system is designed to automatically protect indoor areas and drying clothes from unexpected rainstorms and harsh weather conditions.

### ⚙️ How It Works
1. **Rain Detection:** A Water/Rain Sensor continuously monitors the outdoor environment for moisture or raindrops.
2. **Automated Motion:** When rain is detected, a **Servo Motor** smoothly retracts the clothesline indoors or closes the window.
3. **Status Indicators:** * **Green LED:** Turns ON during clear/dry weather (Safe outside).
   * **Red LED:** Turns ON when rain is detected (Retracted inside).
4. **Smooth Servo Control:** Utilizes incremental angle stepping to ensure a quiet, steady, and mechanical-friendly movement without sudden jerks.

---

## 🚪 2. Smart Face-Recognition Door System
* **Status:** ⏳ Coming Soon 

### 📝 Overview
An advanced keyless entry system that unlocks the main house door using facial recognition technology, eliminating the need for traditional keys or RFID cards.

### ⚙️ How It Works (Planned)
1. **Face Scanning:** A camera module (ESP32-CAM) scans the face of the person approaching the door.
2. **Authentication:** The system compares the live image against stored authorized faces in the database.
3. **Door Access:** * If the face matches, a lock actuator/servo unlocks the door automatically.
   * If an unrecognized face is detected, access is denied, and a security alert is logged.

---

## 🛠️ Built With
* **Microcontrollers:** Arduino Uno / ESP32
* **Sensors & Components:** Rain/Water Sensor, Servo Motor, LEDs, Camera Module
