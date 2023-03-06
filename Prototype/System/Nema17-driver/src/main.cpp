#include <Arduino.h>

#define dirPin 9
#define stepPin 8
#define stepPerRevolution 6400

// motor speed macros
#define motorSpeedFast 100
#define motorSpeedMed 500
#define motorSpeedSlow 1000

// arduino setup and loop functions
void setup() {
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
}

void loop() {
    int i;
    
    digitalWrite(dirPin, HIGH);

    for(i = 0; i < 5 * stepPerRevolution; i++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(motorSpeedFast);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(motorSpeedFast);
    }

    delay(1000);

    digitalWrite(dirPin, LOW);

    for(i = 0; i < 5 * stepPerRevolution; i++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(motorSpeedFast);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(motorSpeedFast);
    }

    delay(1000);
}