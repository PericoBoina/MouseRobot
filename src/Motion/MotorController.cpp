#include"Motion/MotorController.h"

MotorController::MotorController()
{
}

void MotorController::init()
{
    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);
    ledcSetup(ledChannel0, 10000, 8); // 10Khz PWMA
    ledcSetup(ledChannel1, 10000, 8); // 10Khz PWMB
    ledcAttachPin(motorAPwm, ledChannel0);
    ledcAttachPin(motorBPwm, ledChannel1);
}

void MotorController::M1_FWD(int Speed)
{
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, HIGH);
    ledcWrite(ledChannel0, Speed);
}

void MotorController::M2_FWD(int Speed)
{
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, HIGH);
    ledcWrite(ledChannel1, Speed);
}

void MotorController::M1_BKC(int Speed)
{
    digitalWrite(motorA1, HIGH);
    digitalWrite(motorA2, LOW);
    ledcWrite(ledChannel0, Speed);
}

void MotorController::M2_BKC(int Speed)
{
    digitalWrite(motorB1, HIGH);
    digitalWrite(motorB2, LOW);
    ledcWrite(ledChannel1, Speed);
}

void MotorController::M1_Stop()
{
    digitalWrite(motorA1, LOW);
    digitalWrite(motorA2, LOW);
    ledcWrite(ledChannel0, 0);
}

void MotorController::M2_Stop()
{
    digitalWrite(motorB1, LOW);
    digitalWrite(motorB2, LOW);
    ledcWrite(ledChannel1, 0);
}

void MotorController::all_Stop()
{
    M1_Stop();
    M2_Stop();
}