#ifndef StepperMotor_h
#define StepperMotor_h

#include <Arduino.h>

class StepperMotor {
public:
    StepperMotor(bool dir, int In1, int In2, int In3, int In4);
    
    void setStepDuration(int duration);
    void Step_Wave(int numOfSteps);
    void Step_Full(int numOfSteps);
    void Step_Half(int stepCount);

    int duration;
    int currentStep;
    int inputPins[4];
    bool clockwise;
};

#endif