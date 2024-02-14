#include <Arduino.h>
#include <Ultrasonic.h>
#include <ESP32Servo.h>

Servo servo; // create servo object to control a servo
Ultrasonic ultrasonic(??); 

long RangeInCentimeters, leftDistance, rightDistance; // variable to store the range in cm

void moveForward();
void moveBackward();
void turnLeft();
void turnRight();
void moveCircle();
void stop();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2, OUTPUT);   // LED
  pinMode(19, OUTPUT);  // Left Forward
  pinMode(18, OUTPUT);  // Left Backward
  pinMode(5, OUTPUT);   // Right Forward
  pinMode(17, OUTPUT);  // Right Backward
  servo.attach(??); // Servo Pin
  servo.write(90); // Servo Initial Position
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("The distance is: ");
  RangeInCentimeters = ultrasonic.read();  // Range in cm
  Serial.print(RangeInCentimeters);
  Serial.println(" cm");
  delay(250);
}

void stop() {
  digitalWrite(19, LOW);
  digitalWrite(18, LOW);
  digitalWrite(5, LOW);
  digitalWrite(17, LOW);
}

void moveForward() {
  stop();
  delay(500);
  digitalWrite(19, HIGH);
  digitalWrite(18, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(17, LOW);
}

void moveBackward() {
  stop();
  delay(500);
  digitalWrite(19, LOW);
  digitalWrite(18, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(17, HIGH);
}

void turnLeft() {
  stop();
  delay(500);
  digitalWrite(19, LOW);
  digitalWrite(18, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(17, LOW);
  // delay(500);
}

void turnRight() {
  stop();
  delay(500);
  digitalWrite(19, HIGH);
  digitalWrite(18, LOW);
  digitalWrite(5, LOW);
  digitalWrite(17, LOW);
  // delay(500);
}

void moveCircle(){
  moveForward();
  delay(1000);
  turnLeft();
  delay(500);
  moveForward();
  delay(1000);
  turnLeft();
  delay(500);
  moveForward();
  delay(1000);
  turnLeft();
  delay(500);
  moveForward();
  delay(1000);
  turnLeft();
  delay(500);
}

void changePath() {
  stop(); // stop forward movement
  moveBackward(); //add back word-aung
  delay(150);//add move delay-aung
  stop(); //add stop-aung

  servo.write(??);  // check distance to the right
  delay(500);
  rightDistance = ultrasonic.read(); //set right distance
  delay(500);

  servo.write(??);  // check distance to the left
  delay(700);
  leftDistance = ultrasonic.read(); //set left distance
  delay(500);
  
  servo.write(90); // return to center
  delay(100);
  compareDistance();
}

  
void compareDistance()   // find the longest distance
{
  if (leftDistance > rightDistance) { // left is less obstructed 
    turnLeft();
  }
  else if (rightDistance > leftDistance) { // right is less obstructed
    turnRight();
  }
}