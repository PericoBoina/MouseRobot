#ifndef MOTION_H
#define MOTION_H

#include <Arduino.h>
#include "Sensors/Encoders.h" 
#include "Motion/MotorController.h" 

class Motion {
public:
    Motion(Encoders &encoder, MotorController &motor);
    void Straight();


private:
    Encoders &enc;
    MotorController &motor;
    int baseSpeed;
    float integral;
    float lastError;

};

#endif 