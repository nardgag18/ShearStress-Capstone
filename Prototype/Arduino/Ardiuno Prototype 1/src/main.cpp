#include <Arduino.h>
#include <delayCounter.h>
//#include <stepperMotor.h>
#include <string.h>

// pump pin
#define Pump 3 

// sensor pin
#define TempSensor 7

// Stepper motor pins
#define IN1_Stepper 11
#define IN2_Stepper 10
#define IN3_Stepper 9
#define IN4_Stepper 8

// stepper motor rotation delay
# define MotorDelay 1000

// global flag variables
bool checkSensor = false;

// global variables
char rx_byte = 0;
int Humidity = 0;
int Temperature = 0;
int TempComma = 0;
bool SensorError = false;

// Functions used in program

void controlPump(int state) {
  if(state == 1) { // turn on the pump
    digitalWrite(Pump, HIGH);
    Serial.println("Pump On");
  }
  if(state == 0) { // turn off the pump
    digitalWrite(Pump, LOW);
    Serial.println("Pump Off");
  }
}

void DHTSensor() {
  byte Result[45];
  byte DataArray = 0;
  byte DHTData[4];

  long int DataTime = 0;

  bool stopFlag = false;

  pinMode(TempSensor, OUTPUT);
  digitalWrite(TempSensor,HIGH);
  DelayTimer(250000); // Wait 250 milliseconds
  digitalWrite(TempSensor, LOW);
  DelayTimer(30000); // Wait 30 milliseconds
  digitalWrite(TempSensor, HIGH);
  DelayTimer(50);
  pinMode(TempSensor, INPUT);

  do {
    if(digitalRead(TempSensor) == 0 && stopFlag == false) {
      stopFlag = true;
      Result[DataArray]=(micros()-DataTime);
      DataArray++;
      DataTime=micros();
    }
    if (digitalRead(TempSensor) == 1) {
      stopFlag = false;
    }
  } while((micros() - DataTime) < 150);

  for (int i = 2; i < DataArray; i++) {
    if(Result[i] <= 90) {
      Result[i] = 0;
    }
    else {
      Result[i] = 1;
    }
  }
  for (int  j=0; j< 5; j++) {     // redo it for the 5 Bytes (40 Databits /8 = 5)
    for (int  i=0; i< 8; i++) {
      bitWrite(DHTData[j], 7-i, Result[i+2+(j*8)]);
      }  // Create 5 Databytes from the 40 Databits (Ignoring the 2 first Databits)
  }

  // check checksum                            
  if (DHTData[4] == (DHTData[0]+DHTData[1]+DHTData[2]+DHTData[3])){
    Humidity = DHTData[0];
    Temperature = DHTData[2];
    TempComma = DHTData[3];
    SensorError=false;
  } 
  else {
    SensorError=true;
  }
}


// move motor clockwise
void Motor_StepCW() {
  digitalWrite(IN1_Stepper, HIGH);
  digitalWrite(IN2_Stepper, LOW);
  digitalWrite(IN3_Stepper, LOW);
  digitalWrite(IN4_Stepper, LOW);
  DelayTimer(MotorDelay);

  digitalWrite(IN1_Stepper, HIGH);
  digitalWrite(IN2_Stepper, HIGH);
  digitalWrite(IN3_Stepper, LOW);
  digitalWrite(IN4_Stepper, LOW);
  DelayTimer(MotorDelay);

  digitalWrite(IN1_Stepper, LOW);
  digitalWrite(IN2_Stepper, HIGH);
  digitalWrite(IN3_Stepper, LOW);
  digitalWrite(IN4_Stepper, LOW);
  DelayTimer(MotorDelay);

  digitalWrite(IN1_Stepper, LOW);
  digitalWrite(IN2_Stepper, HIGH);
  digitalWrite(IN3_Stepper, HIGH);
  digitalWrite(IN4_Stepper, LOW);
  DelayTimer(MotorDelay);

  digitalWrite(IN1_Stepper, LOW);
  digitalWrite(IN2_Stepper, LOW);
  digitalWrite(IN3_Stepper, HIGH);
  digitalWrite(IN4_Stepper, LOW);
  DelayTimer(MotorDelay);

  digitalWrite(IN1_Stepper, LOW);
  digitalWrite(IN2_Stepper, LOW);
  digitalWrite(IN3_Stepper, HIGH);
  digitalWrite(IN4_Stepper, HIGH);
  DelayTimer(MotorDelay);

  digitalWrite(IN1_Stepper, LOW);
  digitalWrite(IN2_Stepper, LOW);
  digitalWrite(IN3_Stepper, LOW);
  digitalWrite(IN4_Stepper, HIGH);
  DelayTimer(MotorDelay);

  digitalWrite(IN1_Stepper, HIGH);
  digitalWrite(IN2_Stepper, LOW);
  digitalWrite(IN3_Stepper, LOW);
  digitalWrite(IN4_Stepper, HIGH);
  DelayTimer(MotorDelay);
}

// move motor counter-clockwise
void Motor_StepCCW() {
  digitalWrite(IN1_Stepper, HIGH);
  digitalWrite(IN2_Stepper, LOW);
  digitalWrite(IN3_Stepper, LOW);
  digitalWrite(IN4_Stepper, HIGH);
  DelayTimer(MotorDelay);

  digitalWrite(IN1_Stepper, LOW);
  digitalWrite(IN2_Stepper, LOW);
  digitalWrite(IN3_Stepper, LOW);
  digitalWrite(IN4_Stepper, HIGH);
  DelayTimer(MotorDelay);

  digitalWrite(IN1_Stepper, LOW);
  digitalWrite(IN2_Stepper, LOW);
  digitalWrite(IN3_Stepper, HIGH);
  digitalWrite(IN4_Stepper, HIGH);
  DelayTimer(MotorDelay);

  digitalWrite(IN1_Stepper, LOW);
  digitalWrite(IN2_Stepper, LOW);
  digitalWrite(IN3_Stepper, HIGH);
  digitalWrite(IN4_Stepper, LOW);
  DelayTimer(MotorDelay);

  digitalWrite(IN1_Stepper, LOW);
  digitalWrite(IN2_Stepper, HIGH);
  digitalWrite(IN3_Stepper, HIGH);
  digitalWrite(IN4_Stepper, LOW);
  DelayTimer(MotorDelay);

  digitalWrite(IN1_Stepper, LOW);
  digitalWrite(IN2_Stepper, HIGH);
  digitalWrite(IN3_Stepper, LOW);
  digitalWrite(IN4_Stepper, LOW);
  DelayTimer(MotorDelay);

  digitalWrite(IN1_Stepper, HIGH);
  digitalWrite(IN2_Stepper, HIGH);
  digitalWrite(IN3_Stepper, LOW);
  digitalWrite(IN4_Stepper, LOW);
  DelayTimer(MotorDelay);

  digitalWrite(IN1_Stepper, HIGH);
  digitalWrite(IN2_Stepper, LOW);
  digitalWrite(IN3_Stepper, LOW);
  digitalWrite(IN4_Stepper, LOW);
  DelayTimer(MotorDelay);
}

void Motor_Off() {
  digitalWrite(IN1_Stepper, LOW);
  digitalWrite(IN2_Stepper, LOW);
  digitalWrite(IN3_Stepper, LOW);
  digitalWrite(IN4_Stepper, LOW);
}

void MotorStep(bool counterClockWise, int steps) {
  if(steps <= 0) {return;}

  if(counterClockWise) {
    for(int i = 0; i < steps; i++) {
      Motor_StepCCW();
    }
  }
  else {
    for(int i = 0; i < steps; i++) {
      Motor_StepCW();
    }
  }

  Motor_Off();
}

int getMotorSteps() {
  String inString = "";
  bool breakFlag = false;
  int inputSteps = 0;
  Serial.println("GetMotorSteps");
  // ask user how many steps to move motor
  if (Serial.available() > 0) {
    Serial.println("Loop");
    int inChar = Serial.read();
    if(isDigit(inChar)) {
      inString += (char)inChar;
    }
    if(inChar == '\n') {
      inputSteps = inString.toInt();
      breakFlag = true;
    }
  }
  return inputSteps;
}

//StepperMotor motor(true, IN1_Stepper, IN2_Stepper, IN3_Stepper, IN4_Stepper);

// Arduino Setup() and Loop() functions

void setup() {
  Serial.begin(9600);
  Serial.println("Serial Ready");

  // setup pinmodes for pump
  pinMode(Pump, OUTPUT); // replace with pump pin when testing

  // setup pinmodes for stepper motor
  pinMode(IN1_Stepper, OUTPUT);
  pinMode(IN2_Stepper, OUTPUT);
  pinMode(IN3_Stepper, OUTPUT);
  pinMode(IN4_Stepper, OUTPUT);

  controlPump(0);
}

void setup_Protocol() {
   
}

void loop() {
  int pumpState;
  pumpState = 0;
  
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

  Serial.println("Starting Sensor...");
  
  DHTSensor();
  if(SensorError == false) {
    Serial.print("Humidity = "); Serial.print(Humidity); Serial.print("%   Temp. = "); Serial.print(Temperature); Serial.print(" degrees.\n");
    Serial.println("Sensor setup complete");
  }
  else {
    Serial.println("Sensor Error!");
  }
  
  // setup motor and set it in position
  Serial.println("Moving Motor...");
  //MotorStep(false, 500);
  /*
  while(motor.currentStep <= 50000) {
    // spin the motor in a full rotation
    motor.Step_Half(8);
    motor.currentStep++;
    DelayTimer(50);
  }
  */

  Serial.println("Motor in position!");
  Serial.println("Reversing Motor!");
  //MotorStep(true, 500);
  //motor.currentStep = 0;

  /*
  while(motor.currentStep <= 4096) {
    motor.Step_Half(-8);
    motor.currentStep++;
    DelayTimer(50);

  }

  motor.currentStep = 0;
  */
  
  Serial.println("Reversed Motor!");

  ReadyState = 1;
  pumpState = 1;
  controlPump(pumpState);

  Serial.println("Go!");
  
  String inString = "";
  bool breakFlag = false;

  long int Timer_SensorCheck = 501000; // 2.5 seconds
  long int Timer_CompareSensor = 0;
  int c;
  int prevState = 0;
  int numberOfSteps;

  while(GreenLightFlag == 1 && ReadyState == 1) {  
    if((micros() - Timer_CompareSensor ) > Timer_SensorCheck) { // if the given time has passed...
      // check the sensor
      DHTSensor();
      Serial.print("Humidity = "); Serial.print(Humidity); Serial.print("%   Temp. = "); Serial.print(Temperature); Serial.print(" degrees.\n");

      // reset the timer variable to check in 2.5 seconds
      Timer_CompareSensor = micros();
    }
    // GO!
    if (Serial.available() > 0) {
      rx_byte = Serial.read();

      if ((rx_byte >= '0') && (rx_byte <= '9')) {
        Serial.print("Number received: ");
        Serial.println(rx_byte);

        // change the value into an int
        c = atoi(&rx_byte);
        Serial.println(c);
      }
      else { 
        // not a number
      }
    }
    if(prevState != c) {
      prevState = c;
      switch (c) {
        case 0:
          // stop the operation
          ReadyState = 0;
          GreenLightFlag = 0;
          
          pumpState = 0;
          controlPump(pumpState);

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
        case 3:
          // turn off the pump
          pumpState = 0;
          controlPump(pumpState);

          numberOfSteps = 500;
          //int numberOfSteps = getMotorSteps();

          MotorStep(false, numberOfSteps);

          // turn on the pump
          pumpState = 1;
          controlPump(pumpState);
          break;
        case 4:
          // turn off the pump
          pumpState = 0;
          controlPump(pumpState);

          numberOfSteps = 500;
          //int numberOfSteps = getMotorSteps();

          MotorStep(true, numberOfSteps);

          // turn on the pump
          pumpState = 1;
          controlPump(pumpState);
          break;
        default:
          break;
      }
    }
  }
  Serial.println("Finished Operation!"); 
}