# 🏡 Smart House system
> **An integrated, modular home automation and security ecosystem powered by Arduino and Computer Vision.**

---

## 🪟 1. Smart Window

### 🎯 Objective
Protects furniture and laundry from sudden rain, instantly ventilates the house upon detecting toxic gas leaks, and automates window blinds according to ambient outdoor light.

### ⚙️ Mechanism & Core Features

* **🌧️ Rain Protection & Clothesline Control:**
  * **Mechanism:** Continuously monitors ambient moisture and rain levels.
  * **Action:** When rain is detected, a **Servo Motor** retracts the outdoor clothesline indoors or closes the window frame automatically.
  * **Status Indicators:**
    * `🟢 GREEN LED`: Clear / dry weather.
    * `🔴 RED LED`: Rain detected (System retracted).
    * `🔊 Buzzer`: Plays a brief alert tone upon initial rain detection.

* **☀️ Automated Ambient Light Control (LDR Sensor):**
  * **Mechanism:** An LDR sensor measures outdoor light levels.
  * **Action:** Automatically lowers the window blinds at sunset for privacy and opens them at dawn for natural daylighting (includes manual override controls).

* **🚨 Toxic Gas & Fire Safety (MQ-135 Sensor):**
  * **Mechanism:** Monitors indoor air quality for harmful gases, smoke, or LPG leaks.
  * **Action:** Automatically opens the window for emergency ventilation and triggers a continuous audio alarm when dangerous gas levels are detected.

---

## 🛡️ 2. PIR Indoor Security Mode

### 🎯 Objective
Secures internal rooms and hallways against unauthorized movement while occupants are away.

### ⚙️ Mechanism & Core Features

* **🎮 Dual-Button Manual Control:**
  * **Arm Button:** Activates motion tracking mode before leaving.
  * **Disarm Button:** Instantly deactivates the system and silences alarms upon returning.
* **👀 PIR Motion Tracking:** Detects infrared thermal signatures from human bodies within its coverage area.
* **🚨 Dynamic Alarm Response:**
  * **Standby (Armed):** Solid `🟢 GREEN LED` indicates normal active monitoring.
  * **Intrusion Event:**
    1. The `🟢 GREEN LED` turns **OFF** immediately to indicate an active breach.
    2. The `🔴 RED LED` and **Buzzer** blink and beep synchronously in a **realistic siren cycle** (500ms ON / 500ms OFF).
    3. Automatically resets to the Armed standby state once motion clears.

---

## 🔐 3. Ultrasonic Night Perimeter Guard

### 🎯 Objective
Creates a virtual boundary tripwire across doorways and windows that operates exclusively at night to prevent trespassing.

### ⚙️ Mechanism & Core Features

* **🌙 Night-Conditioned Activation (LDR Sensor):**
  * To eliminate daytime false alarms from routine household activity, the distance monitoring algorithm executes **only during dark conditions**.
* **📏 Ultrasonic Boundary Barrier:**
  * Measures distance to the door or wall continuously using an **HC-SR04** sensor.
  * If an intruder breaches the boundary ($< 50\text{ cm}$ threshold), an alarm is triggered instantly.
* **🚨 High-Intensity Siren:**
  * Plays an alternating dual-tone frequency ($2500\text{ Hz} / 1500\text{ Hz}$) along with a flashing Red LED for a police siren effect.
* **⚡ Non-Blocking Execution:** Optimized delays allow instantaneous disarming via the physical button even in the middle of an active alarm.

---

## 🚨 4. Laser & LDR Perimeter Tripwire Security System

### 🎯 Objective
Provides high-precision perimeter security using a visible laser line and LDR sensor to detect unauthorized tripwire breaches immediately.

### ⚙️ Mechanism & Core Features

* **🎮 Dual-Button Dedicated Control:**
  * **Arm Button:** Powers ON the laser diode module and activates perimeter monitoring.
  * **Disarm Button:** Instantly powers OFF the laser module, deactivates monitoring, and silences all alarms.
* **🔴 Visual Status Feedback:**
  * **Disarmed State:** Solid `🔴 RED LED` indicates the system is powered OFF / inactive.
  * **Armed State:** Solid `🟢 GREEN LED` indicates active laser tripwire protection.
* **📡 Laser Tripwire Monitoring:**
  * Continuously measures laser intensity focused directly onto an LDR sensor.
  * If an intruder cuts the laser beam (light intensity drops below threshold):
    1. The `🟢 GREEN LED` turns **OFF** instantly.
    2. The `🔴 RED LED` and **Buzzer** pulse synchronously in 1-second alarm cycles (500ms ON / 500ms OFF).
* **⚡ Energy Efficient & Safe:** The laser module remains completely powered OFF while disarmed to save power and extend component operational lifespan.

---

## ⚡ 5. Smart Energy System

### 🎯 Objective
Optimizes home energy consumption by automatically controlling room illumination based on occupancy and ambient indoor/outdoor light levels.

### ⚙️ Mechanism & Core Features

* **💡 Dual-Condition Smart Automation:**
  * **Daylight Efficiency:** Automatically keeps room lights **OFF** during daytime when natural ambient light is sufficient, regardless of indoor motion.
  * **Occupancy Detection:** Turns lights **ON** automatically only when human presence is detected via the **PIR sensor** in dark environments ($< 500$ LDR threshold).
* **⏱️ Smart Auto-Off Timeout:** Keeps lights illuminated for a set period after the occupant leaves or remains still, preventing sudden shutoffs while eliminating unnecessary energy waste.
* **🔌 Relay Actuation:** Uses an isolated relay module capable of switching standard household AC lighting safely.

---

## 🚪 6. Smart AI Face-Recognition Door System

### 🎯 Objective
Provides keyless, biometric access control using Computer Vision and Artificial Intelligence.

### ⚙️ Mechanism (Planned)

1. **Video Streaming:** An **ESP32-CAM** or USB camera streams live video feeds from the doorway.
2. **AI Authentication:** OpenCV and Python scripts extract facial features in real time and cross-reference them against a pre-registered database.
3. **Access Control:**
   * **Authorized Face:** Triggers a lock actuator/servo to unlock the door automatically.
   * **Unauthorized Face:** Denies access and logs a security entry alert.
