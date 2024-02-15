#include <Arduino.h>
#include <Ultrasonic.h>
#include <ESP32Servo.h>

#define LED 2
// #define IR_R 36
// #define IR_L 39
#define LeftForward 19
#define LeftBackward 18
#define RightForward 5
#define RightBackward 17

Servo servo; // create servo object to control a servo
Ultrasonic ultrasonic(16);  // Ultrasonic Sensor

long RangeInCentimeters, leftDistance, rightDistance; // variable to store the range in cm

void moveForward();
void moveBackward();
void turnLeft();
void turnRight();
void moveCircle();
void stop();
void changePath();
void compareDistance();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED, OUTPUT);   // LED
  pinMode(LeftForward, OUTPUT);  // Left Forward
  pinMode(LeftBackward, OUTPUT);  // Left Backward
  pinMode(RightForward, OUTPUT);   // Right Forward
  pinMode(RightBackward, OUTPUT);  // Right Backward
  // pinMode(IR_R, INPUT);  // IR Right
  // pinMode(IR_L, INPUT);  // IR Left
  servo.attach(21); // Servo Pin
  servo.write(90); // Servo Initial Position
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("The distance is: ");
  RangeInCentimeters = ultrasonic.read();  // Range in cm
  Serial.print(RangeInCentimeters);
  Serial.println(" cm");

  if (RangeInCentimeters < 50) {
    changePath();
  }
  else {
    moveForward();
  }

  delay(250);
  // moveForward();
  // delay(3000);
  // stop();
  // delay(1000);
  // moveBackward();
  // delay(3000);
  // stop();
  // delay(1000);
  // turnLeft();
  // delay(3000);
  // stop();
  // delay(1000);
  // turnRight();
  // delay(3000);
  // stop();
  // delay(1000);
}

void stop() {
  digitalWrite(19, LOW);
  digitalWrite(18, LOW);
  digitalWrite(5, LOW);
  digitalWrite(17, LOW);
}

void moveForward() {
  digitalWrite(19, HIGH);
  digitalWrite(18, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(17, LOW);
}

void moveBackward() {
  digitalWrite(19, LOW);
  digitalWrite(18, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(17, HIGH);
}

void turnLeft() {
  digitalWrite(19, LOW);
  digitalWrite(18, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(17, LOW);
}

void turnRight() {
  digitalWrite(19, HIGH);
  digitalWrite(18, LOW);
  digitalWrite(5, LOW);
  digitalWrite(17, LOW);
}

void changePath() {
  stop(); // stop forward movement
  delay(250); // add stop delay-aung
  moveBackward(); //add back word-aung
  delay(500);//add move delay-aung
  stop(); //add stop-aung
  delay(250); //add stop delay-aung

  servo.write(45);  // check distance to the right
  delay(500);
  rightDistance = ultrasonic.read(); //set right distance
  delay(500);

  servo.write(135);  // check distance to the left
  delay(500);
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
    delay(500);
  }
  else if (rightDistance > leftDistance) { // right is less obstructed
    turnRight();
    delay(500);
  }
  else { // both are equally obstructed
    turnRight();
    delay(1000);
  }
}