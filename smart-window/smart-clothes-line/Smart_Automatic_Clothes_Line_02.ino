#include <Servo.h> // Include the Servo library

Servo myServo; 

// Pin definitions
int waterSensorPin = A0; // Analog pin for the water/rain sensor
int greenLed = 3;        // Digital pin for the green LED (Clear weather indicator)
int redLed = 4;          // Digital pin for the red LED (Rain alert indicator)

// Variable to store the current angle of the servo motor
int currentAngle = 90; 

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud rate
  
  myServo.attach(9);  // Attach the servo motor to digital pin 9
  
  pinMode(greenLed, OUTPUT); // Set green LED pin as output
  pinMode(redLed, OUTPUT);   // Set red LED pin as output
  
  myServo.write(currentAngle); // Set initial servo position to 90 degrees (Outdoors)
}

void loop() {
  // Read the analog value from the water sensor
  int sensorValue = analogRead(waterSensorPin);

  // Print sensor value to Serial Monitor for debugging
  Serial.print("Water Level: ");
  Serial.println(sensorValue);

  // Check if weather is dry (no rain detected)
  if (sensorValue <= 200) {
    digitalWrite(greenLed, HIGH); // Turn ON green LED (Safe/Dry)
    digitalWrite(redLed, LOW);    // Turn OFF red LED

    // Smoothly extend the clothesline outside (move to 90 degrees)
    while (currentAngle < 90) {
      currentAngle += 1;
      myServo.write(currentAngle);
      delay(15); // Adjust speed of motion
    }
  } 
  // Rain detected
  else { 
    digitalWrite(greenLed, LOW); // Turn OFF green LED
    digitalWrite(redLed, HIGH);  // Turn ON red LED (Rain alert)

    // Smoothly retract the clothesline inside (move to 0 degrees)
    while (currentAngle > 0) {
      currentAngle -= 1;
      myServo.write(currentAngle);
      delay(15); // Adjust speed of motion
    }
  }
  delay(200); // Wait 200ms before the next reading
}