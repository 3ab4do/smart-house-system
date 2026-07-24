# 🏡 Smart House System

Welcome to the **Smart House** repository! This project is an ongoing modular home automation system designed to make everyday living safer, smarter, and more convenient using Arduino and Microcontrollers.

---

## 🪟 1. Smart Window & Clothesline System
* **Status:** 🛠️ In Development

### 📝 Overview
An intelligent window automation system designed to respond to changing environmental conditions, protecting indoor areas, improving air safety, and automating natural lighting.

### ⚙️ How It Works & Key Features

1. **🌧️ Rain Protection & Clothesline Control:**
   * **Mechanism:** A Water/Rain Sensor continuously monitors the outdoor environment.
   * **Action:** When rain is detected, a **Servo Motor** smoothly retracts the drying clothes indoors or closes the window to prevent water damage.
   * **Status Indicators:** * **Green LED:** Turns ON during clear/dry weather (Safe outside).
     * **Red LED:** Turns ON when rain is detected (Retracted inside).
     * **Buzzer:** Sounds a one-time alert tone when rain is first detected.

2. **☀️ Ambient Light Control (LDR Sensor):**
   * **Mechanism:** A Light Dependent Resistor (LDR) measures ambient outdoor light levels.
   * **Action:** At sunset or when darkness is detected, the system automatically lowers the window blinds/shutters for privacy. At dawn, it opens them to allow natural daylight inside.
   * **Manual Control:** Includes manual override controls to raise and lower the blinds/curtains on demand.

3. **🚨 Toxic Gas & Fire Safety (MQ-135 Gas Sensor + Buzzer):**
   * **Mechanism:** An MQ-135 Gas Sensor continuously monitors indoor air quality for harmful gases or smoke.
   * **Action:** If a gas leak or smoke is detected, the window opens immediately for ventilation, and a **Buzzer Alarm** sounds loudly to alert occupants of the danger.

---

## 🛡️ 2. Security Mode (PIR Intruder Alarm)
* **Status:** ✅ Completed / Operational

### 📝 Overview
An active motion-detection defense system designed to secure the home against unauthorized entry. It features a simple toggle mechanism (Arm/Disarm) with visual status indicators and a pulsing alarm.

### ⚙️ Key Features & Mechanism
1. **PIR Motion Tracking:** Uses a Passive Infrared (PIR) Sensor to detect infrared motion within its field of view.
2. **Toggle Arm/Disarm Control:** A physical push button allows the user to easily enable (Arm) or disable (Disarm) the security system.
3. **Status Indicators:**
   * **🟢 Green LED:** Solid ON when the system is **Armed** and actively monitoring.
   * **🔴 Red LED:** OFF during standby, blinks rapidly during an intrusion event.
4. **Pulsing Audio & Visual Alarm:**
   * When an intruder is detected while Armed, the system activates a **1-second interval pulsing alarm** (High-pitched buzzer beep + Red LED flashing every 1000ms).

---

## 🚪 3. Smart Face-Recognition Door System
* **Status:** ⏳ Coming Soon

### 📝 Overview
An advanced keyless entry system that unlocks the main house door using facial recognition technology, eliminating the need for traditional keys or RFID cards.

### ⚙️ How It Works (Planned)
1. **Face Scanning:** A camera module (ESP32-CAM) scans the face of the person approaching the door.
2. **Authentication:** The system compares the live image against stored authorized faces in the database.
3. **Door Access:** * If the face matches, a lock actuator/servo unlocks the door automatically.
   * If an unrecognized face is detected, access is denied, and a security alert is logged.
