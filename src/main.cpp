#include <Arduino.h>
#include <Servo.h>

namespace {
constexpr uint8_t encoderClockPin = 2;
constexpr uint8_t encoderDataPin = 3;
constexpr uint8_t encoderButtonPin = 4;
constexpr uint8_t servoPin = 9;
constexpr int minimumAngle = 0;
constexpr int maximumAngle = 180;
constexpr int centerAngle = (minimumAngle + maximumAngle) / 2;
constexpr int angleStep = 10;
// Cambia a -1 si el sentido de giro de tu encoder queda invertido.
constexpr int encoderDirection = -1;
constexpr unsigned long buttonDebounceMs = 30;

// Cada transición válida aporta un cuarto de paso. Los rebotes se cancelan
// al volver por la misma transición en sentido contrario.
constexpr int8_t transitionTable[16] = {
    0, -1, 1, 0,
    1, 0, 0, -1,
    -1, 0, 0, 1,
    0, 1, -1, 0
};

Servo servo;
int currentAngle = centerAngle;
uint8_t previousEncoderState;
int8_t encoderTransitions = 0;
bool previousButtonReading = HIGH;
bool stableButtonState = HIGH;
unsigned long buttonChangedAt = 0;

uint8_t readEncoderState() {
    return (digitalRead(encoderClockPin) << 1) | digitalRead(encoderDataPin);
}

void updateEncoder() {
    const uint8_t state = readEncoderState();
    if (state == previousEncoderState) {
        return;
    }

    // Si cambian ambos canales a la vez, se ha perdido una transición.
    if ((state ^ previousEncoderState) == 3) {
        encoderTransitions = 0;
    } else {
        encoderTransitions += transitionTable[(previousEncoderState << 2) | state];
    }
    previousEncoderState = state;

    // Completar el ciclo evita que un rebote cuente como un giro adicional.
    if (state == 3) {
        if (encoderTransitions == 4 || encoderTransitions == -4) {
            const int direction = encoderTransitions > 0 ? 1 : -1;
            currentAngle = constrain(currentAngle + direction * encoderDirection * angleStep,
                                     minimumAngle, maximumAngle);
            servo.write(currentAngle);
        }
        encoderTransitions = 0;
    }
}

void updateButton() {
    const bool reading = digitalRead(encoderButtonPin);
    const unsigned long now = millis();
    if (reading != previousButtonReading) {
        previousButtonReading = reading;
        buttonChangedAt = now;
    }

    if (reading != stableButtonState && now - buttonChangedAt >= buttonDebounceMs) {
        stableButtonState = reading;
        if (stableButtonState == LOW) {
            currentAngle = centerAngle;
            servo.write(currentAngle);
            encoderTransitions = 0;
            previousEncoderState = readEncoderState();
        }
    }
}
}  // namespace

void setup() {
    pinMode(encoderClockPin, INPUT_PULLUP);
    pinMode(encoderDataPin, INPUT_PULLUP);
    pinMode(encoderButtonPin, INPUT_PULLUP);
    previousEncoderState = readEncoderState();
    servo.attach(servoPin);
    servo.write(currentAngle);
}

void loop() {
    updateEncoder();
    updateButton();
}
