// 1. Pin Definitions
const int trigPin = 9;       // Ultrasonic Sensor Trig pin
const int echoPin = 10;      // Ultrasonic Sensor Echo pin
const int ldrPin = A1;       // LDR Light Sensor pin
const int buttonPin = 3;     // Arm/Disarm Button pin
const int buzzerPin = 8;     // Alarm Buzzer pin
const int redLed = 13;       // Alarm / Danger LED
const int greenLed = 12;     // System Armed LED

// 2. Thresholds
const int DISTANCE_THRESHOLD = 50; // Distance trigger in CM
const int DARK_THRESHOLD = 400;    // LDR Threshold for darkness

// 3. Variables
bool systemArmed = false;
int lastButtonState = HIGH;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  
  // Enable internal pull-up resistor for button
  pinMode(buttonPin, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.println("--- Night Perimeter Security System Started ---");
}

void loop() {
  // --- 1. Button Control (Arm / Disarm) ---
  int buttonState = digitalRead(buttonPin);
  if (buttonState == LOW && lastButtonState == HIGH) {
    systemArmed = !systemArmed; // Toggle System On/Off
    delay(200);                 // Debouncing delay

    if (systemArmed) {
      Serial.println("🟢 System ARMED");
      digitalWrite(greenLed, HIGH);
    } else {
      Serial.println("🔴 System DISARMED");
      digitalWrite(greenLed, LOW);
      digitalWrite(redLed, LOW);
      noTone(buzzerPin);
    }
  }
  lastButtonState = buttonState;

  // --- 2. Security Logic (Only Active when System is ARMED) ---
  if (systemArmed) {
    int lightLevel = analogRead(ldrPin); // Read light level

    // Check if it is Dark enough to activate sensors
    if (lightLevel < DARK_THRESHOLD) {
      
      // Calculate distance using Ultrasonic
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);

      long duration = pulseIn(echoPin, HIGH);
      int distance = duration * 0.034 / 2;

      // Intrusion Check
      if (distance > 0 && distance < DISTANCE_THRESHOLD) {
        Serial.println("🚨 INTRUDER DETECTED IN DARKNESS!");
        triggerSecurityAlarm();
      } else {
        // Safe condition in darkness
        digitalWrite(greenLed, HIGH);
        digitalWrite(redLed, LOW);
        noTone(buzzerPin);
      }

    } else {
      // Daylight condition: Keep armed, but standby
      digitalWrite(greenLed, HIGH);
      digitalWrite(redLed, LOW);
      noTone(buzzerPin);
    }
  }

  delay(50); // Reduced delay for faster system responsiveness
}

// Optimized Alarm Subroutine
void triggerSecurityAlarm() {
  digitalWrite(greenLed, LOW);
  
  // Sound Pattern 1
  digitalWrite(redLed, HIGH);
  tone(buzzerPin, 2500);
  delay(100);

  // Sound Pattern 2
  digitalWrite(redLed, LOW);
  tone(buzzerPin, 1500);
  delay(100);
}