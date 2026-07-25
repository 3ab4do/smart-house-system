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
   * **Status Indicators:**
     * **Green LED:** Turns ON during clear/dry weather (Safe outside).
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

## 🛡️ 2. PIR Security Mode (Motion Detector)
* **Status:** ✅ Completed / Operational

### 📝 Overview
An active indoor motion-detection security module designed to protect rooms and main halls from unauthorized movement using a Passive Infrared (PIR) sensor.

### ⚙️ Key Features & Mechanism
1. **PIR Motion Tracking:** Detects human body heat and infrared movement within its coverage area.
2. **Toggle Arm/Disarm Control:** A physical push button toggles the system state between Armed and Disarmed with software debouncing.
3. **Status Indicators:**
   * **🟢 Green LED:** Solid ON when armed and actively monitoring.
   * **🔴 Red LED:** Blinks during an active intrusion event.
4. **Pulsing Audio & Visual Alarm:**
   * Activates a **1-second interval pulsing alarm** (200ms beep sound + Red LED flashing every 1000ms) upon detecting motion.

---

## 🔐 3. Ultrasonic Security Mode (Night Perimeter Protection)
* **Status:** ✅ Completed / Operational

### 📝 Overview
An intelligent perimeter and doorway defense system combining ultrasonic distance measurements with light sensitivity (LDR) for automated night-time protection.

### ⚙️ Key Features & Mechanism
1. **Manual Arm/Disarm Control:** Activated or deactivated using a physical button toggle for easy manual control.
2. **Night-Only Activation (LDR Sensor):** Uses an LDR to monitor ambient light. Distance checking activates **only during dark conditions**, preventing false alarms during daylight hours.
3. **Distance Boundary Barrier (HC-SR04):** Measures perimeter distance continuously. If an object or intruder breaches the defined distance threshold (< 50 cm), an alert is triggered instantly.
4. **Dual-Frequency Siren:**
   * Alternates sound pitch (2500Hz / 1500Hz) alongside a flashing Red LED for an intense burglar alarm siren effect.
5. **Fast System Response:** Optimized non-blocking delays allow immediate disarming via the toggle button even during an active alarm.

---

## 🚪 4. Smart Face-Recognition Door System
* **Status:** ⏳ Coming Soon

### 📝 Overview
An advanced keyless entry system that unlocks the main house door using facial recognition technology, eliminating the need for traditional keys or RFID cards.

### ⚙️ How It Works (Planned)
1. **Face Scanning:** A camera module (ESP32-CAM) scans the face of the person approaching the door.
2. **Authentication:** The system compares the live image against stored authorized faces in the database.
3. **Door Access:**
   * If the face matches, a lock actuator/servo unlocks the door automatically.
   * If an unrecognized face is detected, access is denied, and a security alert is logged.
