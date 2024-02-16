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

// create servo object to control a servo
Servo servo;

// create an Ultrasonic object
Ultrasonic ultrasonic(16);

// variable to store the range in cm
long RangeInCentimeters, leftDistance, rightDistance;

// 0 is manual mode, 1 is auto mode
int mode = 0;

// Manual Mode
bool forward = 0;
bool backward = 0;
bool left = 0;
bool right = 0;

// Your WiFi credentials.
char ssid[] = "ติ๊งต่าง";
char pass[] = "12345678";

// move functions
void moveForward();
void moveBackward();
void turnLeft();
void turnRight();
void stop();
void manualCar();
void changePath();
void compareDistance();
void autoCar();

// This function is called every time the Virtual Pin 0 state changes
// chang mode
BLYNK_WRITE(V0)
{
    mode = param.asInt();
}

BLYNK_WRITE(V1)
{
    forward = param.asInt();
}

BLYNK_WRITE(V2)
{
    backward = param.asInt();
}

BLYNK_WRITE(V3)
{
    left = param.asInt();
}

BLYNK_WRITE(V4)
{
    right = param.asInt();
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
    // Change Web Link Button message to "Congratulations!"
    Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
    Blynk.setProperty(V3, "onImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
    Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
    digitalWrite(LED, HIGH);
}

void setup()
{
    Serial.begin(9600);
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass); // Blynk
    pinMode(LED, OUTPUT);                      // LED
    pinMode(LeftForward, OUTPUT);              // Left Forward
    pinMode(LeftBackward, OUTPUT);             // Left Backward
    pinMode(RightForward, OUTPUT);             // Right Forward
    pinMode(RightBackward, OUTPUT);            // Right Backward
    pinMode(IR_R, INPUT);                      // IR Right
    pinMode(IR_L, INPUT);                      // IR Left
    servo.attach(21);                          // Servo Pin
    servo.write(90);                           // Servo Initial Position
}

void loop()
{
    Blynk.run();                            // Blynk
    RangeInCentimeters = ultrasonic.read(); // get the range from the sensor
    Serial.print("Distance: ");
    Serial.println(RangeInCentimeters);

    if (mode == 1) // auto mode
    {
        autoCar();
    }
    else if (mode == 0) // manual mode
    {
        manualCar();
    }
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

void manualCar() // manual mode
{
    if (forward)
    {
        moveForward();
    }
    else if (backward)
    {
        moveBackward();
    }
    else if (left)
    {
        turnLeft();
    }
    else if (right)
    {
        turnRight();
    }
    else if (!forward && !backward && !left && !right)
    {
        stop();
    }
}

void changePath() // change path if there is an obstacle
{
    stop();
    delay(250);
    moveBackward();
    delay(500);
    stop();
    delay(250);

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

    // compare the distances
    compareDistance();
}

void compareDistance() // find the longest distance
{
    if (leftDistance > rightDistance) // left is less obstructed
    {
        turnLeft();
        delay(100);
    }
    else if (rightDistance > leftDistance) // right is less obstructed
    {
        turnRight();
        delay(100);
    }
    else // if both distances are equal
    {
        turnRight();
        delay(400);
    }
}

void autoCar() // auto mode
{
    if ((RangeInCentimeters < 30) || (digitalRead(IR_R) == 0) || (digitalRead(IR_L) == 0))
    {
        changePath();
    }
    else
    {
        moveForward();
    }
}
