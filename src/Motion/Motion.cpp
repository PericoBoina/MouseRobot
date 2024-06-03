
#include <Arduino.h>
#include "Motion/Motion.h"
#include "Sensors/Sensor.h"

Motion::Motion()
{
}

void Motion::Straight()
{
    float values[4];
    sensor.update(values);
    float Z = values[3];
    float setpoint = 0; 
    float Kp = 2.780;     
    float Ki = 0.001;     
    float Kd = 0.05;    
    float error = setpoint - Z;
    float P = Kp * error;
    integral += error;
    float I = Ki * integral;
    float derivative = error - lastError;
    float D = Kd * derivative;
    float output = P + I + D;
    lastError = error;
    int leftSpeed = SpeedBase + output;
    int rightSpeed = SpeedBase - output;
     motor.M1_BKC(leftSpeed);
    motor.M2_BKC(rightSpeed);
  
}
