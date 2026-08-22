const int pirPin = 2;          // Digital input pin for PIR motion sensor 
const int armButtonPin = 3;     // Digital input pin for ARM button 
const int disarmButtonPin = 4;  // Digital input pin for DISARM button   
const int buzzerPin = 8;       // Digital output pin for audio alarm buzzer   
const int redLed = 13;         // Digital output pin for Alarm/Alert LED (Red)  
const int greenLed = 12;       // Digital output pin for System Armed LED (Green)

bool systemArmed = false;      // System status flag (true = Armed, false = Disarmed)
int lastArmState = HIGH;       // Previous state for ARM button
int lastDisarmState = HIGH;    // Previous state for DISARM button

void setup() {
  // Configure input pins
  pinMode(pirPin, INPUT);
  
  // Enable internal pull-up resistors for both buttons
  pinMode(armButtonPin, INPUT_PULLUP);
  pinMode(disarmButtonPin, INPUT_PULLUP);

  // Configure output pins
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

  // Initialize Serial Communication for debugging
  Serial.begin(9600);
  Serial.println("--- Home Security System Started ---");
}

void loop() {
  // Read current states of both push buttons
  int armState = digitalRead(armButtonPin);
  int disarmState = digitalRead(disarmButtonPin);
  
  // --- Check ARM Button Press ---
  if (armState == LOW && lastArmState == HIGH) {
    if (!systemArmed) {
      systemArmed = true;
      Serial.println("🟢 System ARMED manually");
      digitalWrite(greenLed, HIGH); // Turn ON green LED
      digitalWrite(redLed, LOW);    // Ensure red LED is OFF
      noTone(buzzerPin);            // Silence buzzer
    }
    delay(150); // Debounce delay
  }

  // --- Check DISARM Button Press ---
  if (disarmState == LOW && lastDisarmState == HIGH) {
    if (systemArmed) {
      systemArmed = false;
      Serial.println("🔴 System DISARMED manually");
      digitalWrite(greenLed, LOW);  // Turn OFF green LED
      digitalWrite(redLed, LOW);    // Turn OFF red LED
      noTone(buzzerPin);            // Silence buzzer
    }
    delay(150); // Debounce delay
  }

  // Save current button states for next iteration
  lastArmState = armState;
  lastDisarmState = disarmState;

  // Execute security check only if the system is ARMED
  if (systemArmed) {
    int motion = digitalRead(pirPin); // Read motion sensor status

    // Trigger alarm if motion is detected
    if (motion == HIGH) {
      Serial.println("🚨 INTRUDER DETECTED! Real Alarm Active!");
      triggerAlarm(); // Call realistic alarm subroutine
    } else {
      // Normal armed status (No motion)
      digitalWrite(greenLed, HIGH); // Keep green LED ON
      digitalWrite(redLed, LOW);    // Keep red LED OFF
      noTone(buzzerPin);            // Silence buzzer
    }
  }
}

// Subroutine for realistic 1-second pulsing alarm
void triggerAlarm() {
  // Step 1: Turn OFF green LED during alarm
  digitalWrite(greenLed, LOW);

  // Step 2: Alarm ON phase (500 milliseconds)
  digitalWrite(redLed, HIGH); // Turn ON warning red LED
  tone(buzzerPin, 2500);      // Play loud alarm tone (2500 Hz)
  delay(500);                 // Active state for half a second

  // Step 3: Alarm OFF phase (500 milliseconds)
  digitalWrite(redLed, LOW);  // Turn OFF warning red LED
  noTone(buzzerPin);          // Stop buzzer sound
  delay(500);                 // Silence state for half a second
}
