#include <Servo.h>

Servo curtainServo;

// --- Pin Definitions ---
const int ldrPin = A0;      // Analog pin for Light Sensor (LDR)
const int whiteLed = 3;     // Digital pin for White LED (Night room light)
const int btnOpenPin = 4;   // Digital pin for Manual Open Button
const int btnClosePin = 5;  // Digital pin for Manual Close Button

// --- State Tracking & Constants ---
bool isCurtainDown = false;
const int fourTurnsTime = 4000; // 4 seconds for 4 full turns

void setup() {
  Serial.begin(9600); // Initialize serial communication
  
  curtainServo.attach(9); // Attach 360-degree servo motor to pin 9
  curtainServo.write(90); // 90 degrees stops the 360-degree continuous servo
  
  pinMode(whiteLed, OUTPUT); // Set White LED pin as output

  // Configure push buttons with internal pull-up resistors
  // Button pressed = LOW, Button released = HIGH
  pinMode(btnOpenPin, INPUT_PULLUP);
  pinMode(btnClosePin, INPUT_PULLUP);
}

void loop() {
  // Read analog value from LDR
  int ldrValue = analogRead(ldrPin);
  
  // Read digital state of manual buttons
  int openBtnState = digitalRead(btnOpenPin);
  int closeBtnState = digitalRead(btnClosePin);

  // Print sensor value for debugging
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  // 1. MANUAL CONTROL: Open Curtain (If Open Button is pressed AND curtain is down)
  if (openBtnState == LOW && isCurtainDown) {
    Serial.println("Manual Override: Opening Curtain...");
    digitalWrite(whiteLed, LOW);   // Turn OFF LED
    
    curtainServo.write(0);        // Rotate counter-clockwise to raise
    delay(fourTurnsTime);
    curtainServo.write(90);       // Stop motor
    
    isCurtainDown = false;        // Update state
  }
  
  // 2. MANUAL CONTROL: Close Curtain (If Close Button is pressed AND curtain is up)
  else if (closeBtnState == LOW && !isCurtainDown) {
    Serial.println("Manual Override: Closing Curtain...");
    digitalWrite(whiteLed, HIGH);  // Turn ON LED
    
    curtainServo.write(180);      // Rotate clockwise to lower
    delay(fourTurnsTime);
    curtainServo.write(90);       // Stop motor
    
    isCurtainDown = true;         // Update state
  }

  // 3. AUTOMATIC CONTROL: Light Sensor (LDR) Logic
  else {
    // Darkness detected -> Lower curtain & Turn ON LED
    if (ldrValue < 300 && !isCurtainDown) {
      digitalWrite(whiteLed, HIGH);
      
      curtainServo.write(180);
      delay(fourTurnsTime);
      curtainServo.write(90);
      
      isCurtainDown = true;
    } 
    // Daylight detected -> Raise curtain & Turn OFF LED
    else if (ldrValue >= 400 && isCurtainDown) {
      digitalWrite(whiteLed, LOW);
      
      curtainServo.write(0);
      delay(fourTurnsTime);
      curtainServo.write(90);
      
      isCurtainDown = false;
    }
  }

  delay(100); // Short delay for loop stability
}
