#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <Arduino.h>

class MotorController
{
public:
    MotorController();
    void init();
    void M1_FWD(int Speed);
    void M2_FWD(int Speed);
    void M1_BKC(int Speed);
    void M2_BKC(int Speed);
    void M1_Stop();
    void M2_Stop();
    void all_Stop();

private:
    const int motorA1 = 16;
    const int motorA2 = 17;
    const int motorAPwm = 12;
    const int motorB1 = 18;
    const int motorB2 = 19;
    const int motorBPwm = 13;
    const int ledChannel0 = 0;
    const int ledChannel1 = 1;
};

#endif
