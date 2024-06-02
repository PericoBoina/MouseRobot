#ifndef Encoders_h
#define Encoders_h

#include <Arduino.h>

class Encoders
{
public:
  Encoders();
  void init();
  int getCount(int encoderNum);
  void reset(int encoderNum);
  float angular_L(); // Velocidad Angular Izquierda (rad/s)
  float angular_R(); // Velocidad Angular Derecha (rad/s)
  float lineal_L();  // Velocidad lineal Izquierda (mm/s)
  float lineal_R();  // Velocidad lineal Derecha (mm/s)

private:
  const int pinA1 = 33;
  const int pinB1 = 32;
  const int pinA2 = 39;
  const int pinB2 = 36;
  volatile int _encoderPos1;
  volatile int _encoderPos2;
  volatile int _lastEncoded1;
  volatile int _lastEncoded2;
  static Encoders *_encoderInstance;
  static void IRAM_ATTR updateEncoder1();
  static void IRAM_ATTR updateEncoder2();
  int lastCountL = 0;
  int lastCountR = 0;
  int countL = 0;
  int countR = 0;
  int dtL = 0;
  int dtR = 0;
  const float pi = 3.14159;
  const int encoderStepsPerRev = 4095;
  const int stepsPerMM = 50;
  const int wheelDiameterMM = 34;
  const int wheelRadiusMM = wheelDiameterMM / 2;
  const float dt = 0.001;
  static const int numSamples = 25;
  float dtLBuffer[numSamples];
  float dtRBuffer[numSamples];
  int dtLIndex = 0;
  int dtRIndex = 0;
};
#endif
