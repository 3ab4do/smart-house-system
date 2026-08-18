// 1. Pin Definitions     
const int ldrPin = A0;          // Analog input pin for LDR sensor 
const int laserPin = 7;         // Digital output pin to power Laser Module 
const int armButtonPin = 3;     // Push button to ARM system 
const int disarmButtonPin = 4;  // Push button to DISARM system 
const int buzzerPin = 8;        // Digital output pin for alarm buzzer  
const int redLed = 13;          // Digital output pin for Red LED (System OFF / Alarm)
const int greenLed = 12;        // Digital output pin for Green LED (System ON / Active)
 
// 2. Thresholds & Variables
const int LIGHT_THRESHOLD = 600; // Adjust according to your laser & room light
bool systemArmed = false;        // System state (true = Armed, false = Disarmed)

int lastArmState = HIGH;         // Button debouncing variable
int lastDisarmState = HIGH;      // Button debouncing variable

void setup() {
  pinMode(laserPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

  // Enable internal pull-up resistors for both buttons
  pinMode(armButtonPin, INPUT_PULLUP);
  pinMode(disarmButtonPin, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.println("--- Dual-Button Laser Security System Started ---");

  // Initial State: System DISARMED (Red LED ON, Green LED OFF, Laser OFF)
  digitalWrite(redLed, HIGH);
  digitalWrite(greenLed, LOW);
  digitalWrite(laserPin, LOW);
}

void loop() {
  // Read states of both buttons
  int armState = digitalRead(armButtonPin);
  int disarmState = digitalRead(disarmButtonPin);

  // --- 1. Check ARM Button Press ---
  if (armState == LOW && lastArmState == HIGH) {
    if (!systemArmed) {
      systemArmed = true;
      Serial.println("🟢 System ARMED - Laser Activated");
      digitalWrite(laserPin, HIGH); // Turn ON laser
      digitalWrite(greenLed, HIGH); // Turn ON Green LED (System Active)
      digitalWrite(redLed, LOW);    // Turn OFF Red LED
      noTone(buzzerPin);            // Silence buzzer
    }
    delay(150); // Debounce delay
  }

  // --- 2. Check DISARM Button Press ---
  if (disarmState == LOW && lastDisarmState == HIGH) {
    if (systemArmed) {
      systemArmed = false;
      Serial.println("🔴 System DISARMED - Laser OFF");
      digitalWrite(laserPin, LOW);  // Turn OFF laser
      digitalWrite(greenLed, LOW);  // Turn OFF Green LED
      digitalWrite(redLed, HIGH);   // Turn ON Red LED (System OFF)
      noTone(buzzerPin);            // Silence buzzer
    }
    delay(150); // Debounce delay
  }

  lastArmState = armState;
  lastDisarmState = disarmState;

  // --- 3. Security Check (Only when system is ARMED) ---
  if (systemArmed) {
    int ldrValue = analogRead(ldrPin); // Read laser intensity on LDR

    // If the beam is cut (Movement detected)
    if (ldrValue < LIGHT_THRESHOLD) {
      Serial.println("🚨 MOTION DETECTED! Laser beam cut!");
      triggerAlarm(); // Execute 1-second pulsing alarm
    } else {
      // Safe Armed State (Beam intact)
      digitalWrite(greenLed, HIGH); // Keep Green LED ON
      digitalWrite(redLed, LOW);    // Keep Red LED OFF
      noTone(buzzerPin);            // Silence buzzer
    }
  }
}

// Subroutine for 1-second pulsing alarm
void triggerAlarm() {
  // Step 1: Turn OFF green LED immediately when motion is detected
  digitalWrite(greenLed, LOW);

  // Step 2: Alarm ON phase (500 milliseconds)
  digitalWrite(redLed, HIGH);  // Turn ON Red LED
  tone(buzzerPin, 2500);       // Play high pitch alarm sound
  delay(500);                  // Wait 0.5s

  // Step 3: Alarm OFF phase (500 milliseconds)
  digitalWrite(redLed, LOW);   // Turn OFF Red LED
  noTone(buzzerPin);           // Stop buzzer
  delay(500);                  // Wait 0.5s
}
