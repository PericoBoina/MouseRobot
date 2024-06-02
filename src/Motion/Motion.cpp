
#include <Arduino.h>
#include "Motion/Motion.h"

Motion::Motion(Encoders &encoder, MotorController &motor)
    : enc(encoder), motor(motor), baseSpeed(baseSpeed), integral(0), lastError(0)
{
}

void Motion::Straight()
{
    float diferencia_pasos = enc.getCount(1) - enc.getCount(2);
    float error = diferencia_pasos;
    float derivative = error - lastError;
    integral += error;
    float KP = 0.801;
    float KI = 0.00012;
    float KD = 2.375;
    float controlSignal = KP * error + KI * integral + KD * derivative;
    int motorSpeedA = baseSpeed - controlSignal;
    int motorSpeedB = baseSpeed + controlSignal;
    motor.M1_FWD(motorSpeedA);
    motor.M2_FWD(motorSpeedB);
    lastError = error;
}
