#include <Arduino.h>
#include <Servo.h>

namespace {
constexpr uint8_t potentiometerPin = A0;
constexpr uint8_t servoPin = 9;
constexpr int minimumAngle = 0;
constexpr int maximumAngle = 180;

Servo servo;
}  // namespace

void setup() {
    servo.attach(servoPin);
}

void loop() {
    const int potentiometerValue = analogRead(potentiometerPin);
    const int angle = map(potentiometerValue, 0, 1023, minimumAngle, maximumAngle);

    servo.write(angle);
    delay(15);
}
