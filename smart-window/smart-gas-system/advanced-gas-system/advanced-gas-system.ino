#include <Servo.h>

// --- Definitions ---

// Servo objects for both sashes
Servo servoRight; 
Servo servoLeft; 

// Pin definitions
const int gasSensorPin = A0; // Analog pin for Gas Sensor (e.g., MQ-135)
const int buzzerPin = 6;     // Digital pin for Buzzer

// Angle constants (adjust these after mechanical installation)
const int angleClosed_R = 0;   // Fully closed angle for Right Servo
const int angleClosed_L = 180; // Fully closed angle for Left Servo

const int angleVent_R = 25;    // Ventilation angle (25 degrees) for Right Servo
const int angleVent_L = 155;   // Ventilation angle (180 - 25) for Left Servo

const int angleEmerg_R = 115;  // Emergency opening angle (115 degrees) for Right Servo
const int angleEmerg_L = 65;   // Emergency opening angle (180 - 115) for Left Servo

// Calibration and Thresholds (Crucial - adjust after testing)
// Hysteresis is added to prevent rapid flapping around the threshold
const int gasThresholdHigh = 350; // Threshold to trigger full opening
const int gasThresholdLow = 300;  // Threshold to return to ventilation

// State tracking variable
bool isEmergencyOpen = false;

void setup() {
  Serial.begin(9600); // Initialize serial monitor

  // Attach servos to pins 9 and 10
  servoRight.attach(9);
  servoLeft.attach(10);

  // Initialize servos in the ventilation (25 degree) position as a default safe start
  Serial.println("System starting... Setting to Ventilation Mode.");
  writeServos(angleVent_R, angleVent_L);
  isEmergencyOpen = false;

  pinMode(buzzerPin, OUTPUT); // Set buzzer as output
}

void loop() {
  // 1. Read Gas Level
  int gasValue = analogRead(gasSensorPin);
  
  // Print value to Serial Monitor for testing and debugging
  Serial.print("Gas Level: ");
  Serial.println(gasValue);

  // 2. Logic Control based on Hysteresis and State

  // Case A: Gas detected (Emergency condition)
  // If gas exceeds the high threshold AND the window is not already emergency open
  if (gasValue > gasThresholdHigh && !isEmergencyOpen) {
    Serial.println("!!! ALERT: High Gas Detected. OPENING WINDOWS 115 DEGREES !!!");
    
    // Smoothly open windows to 115 degrees
    smoothServoMove(servoRight, servoLeft, angleVent_R, angleVent_L, angleEmerg_R, angleEmerg_L);
    
    digitalWrite(buzzerPin, HIGH); // Sound the alarm
    isEmergencyOpen = true;        // Update state
  }

  // Case B: Gas levels decrease (Safe condition)
  // If gas drops below the low threshold AND the window is emergency open
  else if (gasValue < gasThresholdLow && isEmergencyOpen) {
    Serial.println("... Gas Levels Normal. Returning to 25 Degree Ventilation.");
    
    // Smoothly return windows to 25 degrees
    smoothServoMove(servoRight, servoLeft, angleEmerg_R, angleEmerg_L, angleVent_R, angleVent_L);
    
    digitalWrite(buzzerPin, LOW); // Turn off the alarm
    isEmergencyOpen = false;      // Update state
  }

  // Small delay for stability before next reading
  delay(500); 
}

// --- Helper Functions ---

// Function to set both servos to specific angles immediately
void writeServos(int rightAngle, int leftAngle) {
  servoRight.write(rightAngle);
  servoLeft.write(leftAngle);
}

// Function to move both servos smoothly together
void smoothServoMove(Servo& sRight, Servo& sLeft, int startR, int startL, int endR, int endL) {
  // Use the larger angle change to determine the number of steps
  int steps = max(abs(startR - endR), abs(startL - endL));
  
  // Create a step factor for both servos
  float stepFactorR = (float)(endR - startR) / steps;
  float stepFactorL = (float)(endL - startL) / steps;

  for (int i = 0; i <= steps; i++) {
    int currentAngleR = startR + (i * stepFactorR);
    int currentAngleL = startL + (i * stepFactorL);
    
    sRight.write(currentAngleR);
    sLeft.write(currentAngleL);
    
    // Slow down the movement. Adjust the 15 for speed control (smaller is faster)
    delay(15); 
  }
}