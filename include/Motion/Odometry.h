#ifndef ODOMETRY_H
#define ODOMETRY_H

#include "Sensors/Encoders.h"

class Odometry
{
public:
    Odometry(); 
    void update();

private:
    Encoders encoders; 
    int lastEncoderPos_L;
    int lastEncoderPos_R;
    const float distanciaEntreRuedas_mm;
    const int ticksPorMilimetro;
    float x;     // Posición x
    float y;     // Posición y
    float theta; // Orientación angular
};

#endif
