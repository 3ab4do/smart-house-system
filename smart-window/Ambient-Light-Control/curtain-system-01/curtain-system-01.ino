#include <Servo.h>

Servo curtainServo;

// Pin definitions
int ldrPin = A0;      // Analog pin for Light Sensor (LDR)
int whiteLed = 3;     // Digital pin for White LED (Night room light)

// State tracking variable (prevents continuous motor rotation)
bool isCurtainDown = false;

// Time required for 4 full rotations (4000ms = approx 4 seconds)
// Adjust this duration based on your servo motor's exact speed
const int fourTurnsTime = 4000; 

void setup() {
  Serial.begin(9600); // Initialize serial communication
  
  curtainServo.attach(9); // Attach 360-degree servo motor to pin 9
  curtainServo.write(90); // 90 degrees stops the 360-degree continuous servo
  
  pinMode(whiteLed, OUTPUT); // Set White LED pin as output
}

void loop() {
  // Read analog value from the LDR sensor
  int ldrValue = analogRead(ldrPin);
  
  // Print sensor value to Serial Monitor for debugging
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  // 1. Darkness detected (Lower the curtain with 4 rotations & turn ON White LED)
  if (ldrValue < 300 && !isCurtainDown) {
    digitalWrite(whiteLed, HIGH); // Turn ON White LED (Night light)

    // Rotate clockwise to lower the curtain
    curtainServo.write(180); // Full speed clockwise
    delay(fourTurnsTime);    // Wait for 4 full turns
    curtainServo.write(90);  // Stop the motor

    isCurtainDown = true;    // Update state to indicate curtain is down
  } 

  // 2. Daylight detected (Raise the curtain with 4 rotations & turn OFF White LED)
  else if (ldrValue >= 400 && isCurtainDown) {
    digitalWrite(whiteLed, LOW);  // Turn OFF White LED (Daytime)

    // Rotate counter-clockwise to raise the curtain
    curtainServo.write(0);   // Full speed counter-clockwise
    delay(fourTurnsTime);    // Wait for 4 full turns
    curtainServo.write(90);  // Stop the motor

    isCurtainDown = false;   // Update state to indicate curtain is raised
  }

  delay(200); // Read sensor every 200ms
}