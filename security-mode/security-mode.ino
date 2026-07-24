// 1. Pin Definitions
const int pirPin = 2;       // Digital input pin for PIR motion sensor
const int buttonPin = 3;    // Digital input pin for Arm/Disarm push button
const int buzzerPin = 8;    // Digital output pin for audio alarm buzzer
const int redLed = 13;      // Digital output pin for Alarm/Alert LED (Red)
const int greenLed = 12;    // Digital output pin for System Armed LED (Green)

// 2. Global Variables
bool systemArmed = false;   // System status flag (true = Armed, false = Disarmed)
int lastButtonState = HIGH; // Stores the previous state of the button

void setup() {
  // Configure input pins
  pinMode(pirPin, INPUT);
  
  // Enable internal pull-up resistor to avoid floating input on the button
  pinMode(buttonPin, INPUT_PULLUP); 

  // Configure output pins
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

  // Initialize Serial Communication for debugging
  Serial.begin(9600);
  Serial.println("--- Home Security System Started ---");
}

void loop() {
  // Read the current state of the push button
  int buttonState = digitalRead(buttonPin);
  
  // Detect button press transition (Falling edge: HIGH to LOW)
  if (buttonState == LOW && lastButtonState == HIGH) {
    systemArmed = !systemArmed; // Toggle system state between Armed and Disarmed
    delay(200);                 // Software debouncing delay to prevent false triggers

    // Update status indicators based on current state
    if (systemArmed) {
      Serial.println("🟢 System ARMED (Security Active)");
      digitalWrite(greenLed, HIGH); // Turn ON green LED
      digitalWrite(redLed, LOW);    // Ensure red LED is OFF
      noTone(buzzerPin);            // Silence buzzer
    } else {
      Serial.println("🔴 System DISARMED (Standby)");
      digitalWrite(greenLed, LOW);  // Turn OFF green LED
      digitalWrite(redLed, LOW);    // Turn OFF red LED
      noTone(buzzerPin);            // Silence buzzer
    }
  }
  
  // Save current button state for the next iteration
  lastButtonState = buttonState;

  // Execute security check only if the system is ARMED
  if (systemArmed) {
    int motion = digitalRead(pirPin); // Read motion sensor status

    // Trigger alarm if motion is detected
    if (motion == HIGH) {
      Serial.println("🚨 INTRUDER DETECTED! Alarm Active!");
      triggerAlarm(); // Call alarm subroutine
    }
  }
}

// Subroutine to handle periodic 1-second alarm sound and visual blink
void triggerAlarm() {
  // --- BEEP ON (200 milliseconds) ---
  digitalWrite(redLed, HIGH); // Turn ON warning LED
  tone(buzzerPin, 2000);      // Play a high-pitched 2000 Hz beep tone
  delay(200);                 // Beep duration

  // --- SILENCE OFF (800 milliseconds) ---
  digitalWrite(redLed, LOW);  // Turn OFF warning LED
  noTone(buzzerPin);          // Stop the buzzer tone
  delay(800);                 // Silence duration to complete 1 full second (200ms + 800ms = 1000ms)
}