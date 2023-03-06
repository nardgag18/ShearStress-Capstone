/* 
    Test the operation of the relay module 
    with the aquarium pump. Relay module is connected 
    to NC connection on the relay module.
*/

#include <Arduino.h>

#include "pump.hpp"

typedef enum {on, off} pumpPower;
int i = 0;
void setup() {
  pinMode(pumpPin, OUTPUT);
  digitalWrite(pumpPin, HIGH); // start with pump off
}

void loop() {
  i = togglePumpOn(); // turn on the pump
  delay(5000); // run the pump for 5 seconds
  i = togglePumpOff(); // turn off the pump
  while(1) {} // stop the loop to keep pump off
}