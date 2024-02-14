#include <Arduino.h>

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
  digitalWrite(2, HIGH);
}

void loop() {
  moveCircle();
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