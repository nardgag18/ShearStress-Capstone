#include <Arduino.h>
#include <stepperMotor.h>
#include <delayCounter.h>

StepperMotor::StepperMotor(bool dir, int In1, int In2, int In3, int In4) {
    this->inputPins[0] = In1;
    this->inputPins[1] = In2;
    this->inputPins[2] = In3;
    this->inputPins[3] = In4;
    this->clockwise = dir;
    this->currentStep = 0;
    for(int inputCount = 0; inputCount < 4; inputCount++) {
        pinMode(this->inputPins[inputCount], OUTPUT);
    }
    this->duration = 10;
    
}

void StepperMotor::setStepDuration(int duration) {
    this->duration = duration;
}

void StepperMotor::Step_Half(int stepCount) {
    //int halfStepCount = 8;
    //int targetSteps = 4096;
    int halfStepSequence[][4] {
        {1,0,0,0},
        {1,1,0,0},
        {0,1,0,0},
        {0,1,1,0},
        {0,0,1,0},
        {0,0,1,1},
        {0,0,0,1},
        {1,0,0,1}
    };

    int currentStepInSequence = currentStep % stepCount;
    int directionStep = clockwise ? currentStepInSequence : (stepCount - 1) - currentStepInSequence;

    for(int pin = 0; pin < 4; pin++) {
        digitalWrite(inputPins[pin], halfStepSequence[directionStep][pin]);
    }
}