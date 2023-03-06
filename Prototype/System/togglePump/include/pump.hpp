#include <Arduino.h>

#define pumpPin 13

int togglePumpOn() 
{
    // turn on the pump
    digitalWrite(pumpPin, LOW);

    // return pump is on
    return 1;
}

int togglePumpOff()
{
    // turn off pump
    digitalWrite(pumpPin, HIGH);

    // return pump is off
    return 0;
}