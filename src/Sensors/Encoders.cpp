#include "Sensors/Encoders.h"

Encoders *Encoders::_encoderInstance = nullptr;

Encoders::Encoders()
{
  _encoderInstance = this;
}

void Encoders::init()
{
  pinMode(pinA1, INPUT_PULLUP);
  pinMode(pinB1, INPUT_PULLUP);
  pinMode(pinA2, INPUT_PULLUP);
  pinMode(pinB2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinA1), updateEncoder1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinB1), updateEncoder1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinA2), updateEncoder2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinB2), updateEncoder2, CHANGE);
}

void IRAM_ATTR Encoders::updateEncoder1()
{
  int MSB1 = digitalRead(_encoderInstance->pinA1);
  int LSB1 = digitalRead(_encoderInstance->pinB1);
  int encoded1 = (MSB1 << 1) | LSB1;
  int sum1 = (_encoderInstance->_lastEncoded1 << 2) | encoded1;
  if ((sum1 == 0b1101) || (sum1 == 0b0100) || (sum1 == 0b0010) || (sum1 == 0b1011))
  {
    _encoderInstance->_encoderPos1++;
  }
  else if ((sum1 == 0b1110) || (sum1 == 0b0111) || (sum1 == 0b0001) || (sum1 == 0b1000))
  {
    _encoderInstance->_encoderPos1--;
  }
  _encoderInstance->_lastEncoded1 = encoded1;
}

void IRAM_ATTR Encoders::updateEncoder2()
{
  int MSB2 = digitalRead(_encoderInstance->pinA2);
  int LSB2 = digitalRead(_encoderInstance->pinB2);
  int encoded2 = (MSB2 << 1) | LSB2;
  int sum2 = (_encoderInstance->_lastEncoded2 << 2) | encoded2;
  if ((sum2 == 0b1101) || (sum2 == 0b0100) || (sum2 == 0b0010) || (sum2 == 0b1011))
  {
    _encoderInstance->_encoderPos2++;
  }
  else if ((sum2 == 0b1110) || (sum2 == 0b0111) || (sum2 == 0b0001) || (sum2 == 0b1000))
  {
    _encoderInstance->_encoderPos2--;
  }
  _encoderInstance->_lastEncoded2 = encoded2;
}

int Encoders::getCount(int encoderNum)
{
  if (encoderNum == 1)
  {
    return _encoderPos1;
  }
  else if (encoderNum == 2)
  {
    return _encoderPos2;
  }
  else
  {
    return 0;
  }
}

void Encoders::reset(int encoderNum)
{
  if (encoderNum == 1)
  {
    _encoderPos1 = 0;
  }
  if (encoderNum == 2)
  {
    _encoderPos2 = 0;
  }
}

float Encoders::angular_L()
{
  lastCountL = countL;
  countL = getCount(1);
  float dtL = static_cast<float>(lastCountL - countL);
  dtLBuffer[dtLIndex] = dtL;
  float sumL = 0.0;
  for (int i = 0; i < numSamples; ++i)
  {
    sumL += dtLBuffer[i];
  }
  dtLIndex = (dtLIndex + 1) % numSamples;
  float ang_L = (sumL / numSamples / encoderStepsPerRev) * (2.0 * pi);
  float omega_L = ang_L / dt;
  return omega_L;
}
float Encoders::angular_R()
{
  lastCountR = countR;
  countR = getCount(2);
  float dtR = static_cast<float>(lastCountR - countR);
  dtRBuffer[dtRIndex] = dtR;
  float sumR = 0.0;
  for (int i = 0; i < numSamples; ++i)
  {
    sumR += dtRBuffer[i];
  }
  dtRIndex = (dtRIndex + 1) % numSamples;
  float ang_R = (sumR / numSamples / encoderStepsPerRev) * (2.0 * pi);
  float omega_R = ang_R / dt;
  return omega_R;
}

float Encoders::lineal_L()
{
  float lineal_L = angular_L() * wheelRadiusMM;
  return lineal_L;
}

float Encoders::lineal_R()
{
  float lineal_R = angular_R() * wheelRadiusMM;
  return lineal_R;
}
