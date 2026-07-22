#include <Servo.h>

Servo servoRight; 
Servo servoLeft; 

int gasAnalog = A0;
int buzzer = 3;
int redLed = 4;

void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(redLed, OUTPUT);
  servoRight.attach(9);
  servoLeft.attach(10);
}

void loop() { 
  int gasValue = analogRead(gasAnalog);
  Serial.println(gasValue);

  if (gasValue >= 300) {
    digitalWrite(redLed, HIGH);
    digitalWrite(buzzer, HIGH);
    
    servoRight.write(115); 
    servoLeft.write(65);  
  }

  if (gasValue <= 200) { 
    digitalWrite(redLed, LOW);
    digitalWrite(buzzer, LOW);
    
    servoRight.write(25);  
    servoLeft.write(155); 
  }

  delay(200);
}