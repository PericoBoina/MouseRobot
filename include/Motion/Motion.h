#ifndef MOTION_H
#define MOTION_H

#include <Arduino.h>
#include "Sensors/Encoders.h"
#include "Motion/MotorController.h"
#include "Sensors/Sensor.h"

#define SpeedBase 140

class Motion
{
public:
    Motion();
    void Straight();

private:
    Encoders enc;
    MotorController motor;
    Sensor sensor;
    float integral;
    float lastError;
};

#endif