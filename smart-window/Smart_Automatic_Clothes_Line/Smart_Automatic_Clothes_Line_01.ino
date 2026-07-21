#include <Servo.h> // servo library

Servo myServo; 

int waterSensorPin = A0;
int greenLed = 3;
int redLed = 4;

void setup() {
  Serial.begin(9600);
  myServo.attach(9);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(waterSensorPin);

  Serial.print("Water Level: ");
  Serial.println(sensorValue);

  // if water value < or = 200
  if (sensorValue <= 200) {
    myServo.write(90);
    digitalWrite(greenLed, HIGH); // green led on when there is not water
    digitalWrite(redLed, LOW);
  } 
  else { // if water value > 200
    myServo.write(67);
    delay(1000);
    myServo.write(45);
    delay(1000);
    myServo.write(22);
    delay(1000);
    myServo.write(0);
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH); // red led on when there is water
  }

  delay(200); // wait 0.2 sec
}