#define BLYNK_TEMPLATE_ID "TMPL65o3f4u3m"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "HSgM8vYDNFM_cv1BJr1TmDSu8rgl_zfN"
#define BLYNK_PRINT Serial

#include <Arduino.h>
#include <Ultrasonic.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define LED 2
#define IR_R 36
#define IR_L 39
#define LeftForward 19
#define LeftBackward 18
#define RightForward 5
#define RightBackward 17

Servo servo;               // create servo object to control a servo
Ultrasonic ultrasonic(16); // Ultrasonic Sensor

long RangeInCentimeters, leftDistance, rightDistance; // variable to store the range in cm
int state = 0;

char ssid[] = "ติ๊งต่าง";
char pass[] = "12345678";

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
    // Set incoming value from pin V0 to a variable
    int value = param.asInt();

    // Update state
    Blynk.virtualWrite(V1, value);

    state = value;

    // If value is 1, turn on LED
    if (value == 1)
    {
        digitalWrite(LED, HIGH);
    }
    else
    {
        digitalWrite(LED, LOW);
    }
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
    // Change Web Link Button message to "Congratulations!"
    Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
    Blynk.setProperty(V3, "onImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
    Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

void moveForward();
void moveBackward();
void turnLeft();
void turnRight();
void stop();
void changePath();
void compareDistance();

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(LED, OUTPUT);           // LED
    pinMode(LeftForward, OUTPUT);   // Left Forward
    pinMode(LeftBackward, OUTPUT);  // Left Backward
    pinMode(RightForward, OUTPUT);  // Right Forward
    pinMode(RightBackward, OUTPUT); // Right Backward
    pinMode(IR_R, INPUT);           // IR Right
    pinMode(IR_L, INPUT);           // IR Left
    servo.attach(21);               // Servo Pin
    servo.write(90);                // Servo Initial Position
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
    // put your main code here, to run repeatedly:
    Blynk.run();
    RangeInCentimeters = ultrasonic.read(); // Range in cm
    Blynk.virtualWrite(V4, RangeInCentimeters);
    Blynk.virtualWrite(V2, digitalRead(IR_R));
    Blynk.virtualWrite(V3, digitalRead(IR_L));
    Serial.println(RangeInCentimeters);

    if (state == 1) // if the button is pressed
    {
        if ((RangeInCentimeters < 30) || (digitalRead(IR_R) == 0) || (digitalRead(IR_L) == 0))
        {
            changePath();
        }
        else
        {
            moveForward();
        }
        delay(250);
    }
    else if (state == 0) // if the button is not pressed
    {
        stop();
    }

    delay(250);
}

void stop()
{
    digitalWrite(19, LOW);
    digitalWrite(18, LOW);
    digitalWrite(5, LOW);
    digitalWrite(17, LOW);
}

void moveForward()
{
    digitalWrite(19, HIGH);
    digitalWrite(18, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(17, LOW);
}

void moveBackward()
{
    digitalWrite(19, LOW);
    digitalWrite(18, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(17, HIGH);
}

void turnLeft()
{
    digitalWrite(19, LOW);
    digitalWrite(18, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(17, LOW);
}

void turnRight()
{
    digitalWrite(19, HIGH);
    digitalWrite(18, LOW);
    digitalWrite(5, LOW);
    digitalWrite(17, LOW);
}

void changePath()
{
    stop();         // stop forward movement
    delay(250);     // add stop delay-aung
    moveBackward(); // add back word-aung
    delay(500);     // add move delay-aung
    stop();         // add stop-aung
    delay(250);     // add stop delay-aung

    servo.write(45); // check distance to the right
    delay(500);
    rightDistance = ultrasonic.read(); // set right distance
    delay(500);

    servo.write(135); // check distance to the left
    delay(500);
    leftDistance = ultrasonic.read(); // set left distance
    delay(500);

    servo.write(90); // return to center
    delay(100);

    compareDistance();
}

void compareDistance() // find the longest distance
{
    if (leftDistance > rightDistance)
    { // left is less obstructed
        turnLeft();
        delay(100);
    }
    else if (rightDistance > leftDistance)
    { // right is less obstructed
        turnRight();
        delay(100);
    }
    else
    { // both are equally obstructed
        turnRight();
        delay(400);
    }
}