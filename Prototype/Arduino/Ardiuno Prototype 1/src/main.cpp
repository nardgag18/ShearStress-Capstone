#include <Arduino.h>

#define Pump 2 // turn the pump on and off
#define SW1 7 // turn on and off stepper motor
#define SW2 6 // turn on and off stepper motor
#define SW3 5 // rotate stepper motor in counter_clockwise direction
#define SW4 4 // rotate stepper motor in clockwise direction

enum Pump_Control {On = 1, Off = 0}; // pump control
enum Motor_Control {Stop = 0, Clockwise = 1, Counter_Clockwise = 2}; // Motor control

/*
class Motor {
  public:
    enum Mode {Clockwise, Counter_Clockwise, Off}; 

};
*/

class Button {
  private:
    uint8_t pinNum;
    uint16_t state;

  public:
    void setButton(int pin) {
      pinNum = pin;
      state = 0;
      pinMode(pinNum, INPUT_PULLUP);
    }
    bool debounce() {
      state = (state<<1) | digitalRead(pinNum) | 0xfe00;
      return (state = 0xfe00);
    }
};

void controlPump(int state) {
  if(state == 1) { // turn on the pump
    digitalWrite(Pump, HIGH);
  }
  else {
    digitalWrite(Pump, LOW);
  }
}

Button btn1;
//Button btn2;
//Button btn3;
//Button btn4;

void setup() {
  // setup pinmodes for pump and stepper motor
  pinMode(Pump, OUTPUT); // replace with pump pin when testing
  
  btn1.setButton(SW1);
  //btn2.setButton(SW2);
  //btn3.setButton(SW3);
  //btn4.setButton(SW4);

  controlPump(0);
}



void loop() {
  int pumpState;
  pumpState = 0;
  //Motor_Control motorState;
  //motorState = Stop;
  
  // debounce switches 
  if(!btn1.debounce()) {
    // turn on/off pump
    if(pumpState == 1) {
      controlPump(0);
      pumpState = 0;
    }
    if(pumpState == 0) {
      controlPump(1);
      pumpState = 1;
    }
  }
  /*
  if(btn2.debounce()) {
    // turn on/off stepper motor
    if(motorState != Stop) {
      motorState = Stop;
      
    }
  }
  */


}