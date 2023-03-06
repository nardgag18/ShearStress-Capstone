#include <Arduino.h>

void DelayTimer(long int timeRequest) {
  long int timePassed = micros();
  do {} while( (micros() - timePassed) < timeRequest);
}