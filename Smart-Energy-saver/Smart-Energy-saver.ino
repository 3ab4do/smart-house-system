// 1. Pin Definitions          
const int pirPin = 2;       // PIR Motion Sensor    
const int ldrPin = A0;      // LDR Light Sensor 
const int relayPin = 7;     // Relay Module (Controls Room Light)    
const int greenLed = 12;    // System Active Indicator    

// 2. Thresholds & Variables
const int DARK_THRESHOLD = 500; // LDR threshold for darkness 
unsigned long lastMotionTime = 0;
const unsigned long LIGHT_TIMEOUT = 10000; // Keep light ON for 10 seconds after motion stops

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(ldrPin, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(greenLed, OUTPUT);

  // Default: Turn OFF Light Relay (Active LOW or HIGH depending on relay module)
  digitalWrite(relayPin, LOW); 
  digitalWrite(greenLed, HIGH); // System ON indicator

  Serial.begin(9600);
  Serial.println("--- Smart Energy Lighting System Active ---");
}

void loop() {
  int lightLevel = analogRead(ldrPin); // Read room light
  int motionDetected = digitalRead(pirPin); // Read human motion

  // Check if room is DARK and MOTION is detected
  if (lightLevel < DARK_THRESHOLD) {
    if (motionDetected == HIGH) {
      Serial.println("💡 Dark room + Motion detected -> Turning Light ON");
      digitalWrite(relayPin, HIGH); // Turn ON Room Lamp
      lastMotionTime = millis();    // Reset timer
    } 
    // Keep light ON for a few seconds after last motion
    else if (millis() - lastMotionTime < LIGHT_TIMEOUT && lastMotionTime > 0) {
      digitalWrite(relayPin, HIGH); // Keep light ON
    } 
    else {
      digitalWrite(relayPin, LOW);  // Turn OFF light (No motion timeout)
    }
  } else {
    // Daylight condition: Keep lights OFF regardless of motion to save energy
    digitalWrite(relayPin, LOW);
  }

  delay(200); // Stability delay
}
