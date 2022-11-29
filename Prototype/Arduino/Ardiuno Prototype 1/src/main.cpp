#include <Arduino.h>
//#include <string.h>

#define Pump 2 // turn the pump on and off

char rx_byte = 0;

void controlPump(int state) {
  if(state == 1) { // turn on the pump
    //digitalWrite(Pump, HIGH);
    Serial.println("Pump On");
  }
  if(state == 0) { // turn off the pump
    //digitalWrite(Pump, LOW);
    Serial.println("Pump Off");
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Serial Ready");

  // setup pinmodes for pump
  pinMode(Pump, OUTPUT); // replace with pump pin when testing

  controlPump(0);
}

void setup_Protocol() {
  // get number of motor steps
  Serial.println("How many motor steps?");
  //int steps 
}

void loop() {
  int pumpState;
  pumpState = 0;

  //Motor_Control motorState;
  //motorState = Stop;
  
  int GreenLightFlag = 0; // raspberry pi flag (0 = don't go)
  int ReadyState = 0; // arduino ready state (0 = not ready)
  
  // do setup protocol with raspberry pi
  Serial.println("Setup protocol completed");
  
  // wait for start signal
  Serial.println("Waiting...");
  while(GreenLightFlag != 1) {
    if (Serial.available() > 0) {
      rx_byte = Serial.read();

      if(rx_byte == '1') {
        GreenLightFlag = 1;
      }
    }
  }
  
  Serial.println("Moving Motor...");

  // setup motor and set it in position
  Serial.println("Motor in position!");
  
  ReadyState = 1;
  pumpState = 1;
  controlPump(pumpState);

  Serial.println("Go!");
  
  while(GreenLightFlag == 1 && ReadyState == 1) {
    // GO!
    if (Serial.available() > 0) {
      rx_byte = Serial.read();

      if ((rx_byte >= '0') && (rx_byte <= '9')) {
        Serial.print("Number received: ");
        Serial.println(rx_byte);

        // change the value into an int
        int c = atoi(&rx_byte);
        Serial.println(c);

        switch (c)
        {
        case 0:
          // stop the operation
          ReadyState = 0;
          GreenLightFlag = 0;
          Serial.println("Stopping!");
          break;
        case 1:
          // turn off the pump
          if (pumpState != 0) {
            pumpState = 0;
            controlPump(pumpState);
          }
          else {
            Serial.println("Pump already off");
          }
          break;
        case 2:
          // turn on the pump
          if (pumpState != 1) {
            pumpState = 1;
            controlPump(pumpState);
          }
          else {
            Serial.println("Pump already on");
          }
          break;
        default:
          break;
        }
      }
      else {
        Serial.println("Not a number.");
      }
    }
  }
  Serial.println("Finished Operation!");
    /*
    if (Serial.available() > 0) {    // is a character available?
      rx_byte = Serial.read();       // get the character
    
      // check if a number was received
      if ((rx_byte >= '0') && (rx_byte <= '9')) {
        Serial.print("Number received: ");
        Serial.println(rx_byte);
      }
      else {
        Serial.println("Not a number.");
      }
    } // end: if (Serial.available() > 0)
    */
      // turn on the pump

      // begin the timer
  //}
}