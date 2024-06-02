#include "Add/Buttons.h"

void Buttons::init()
{
    pinMode(SW2_PIN, INPUT);
    pinMode(SW3_PIN, INPUT);
}

bool Buttons::SW2()
{
    bool lectura = digitalRead(SW2_PIN);
    bool pulsado = (lectura == HIGH && !estadoAnteriorSW2);
    estadoAnteriorSW2 = lectura;
    return pulsado;
}

bool Buttons::SW3()
{
    bool lectura = digitalRead(SW3_PIN);
    bool pulsado = (lectura == HIGH && !estadoAnteriorSW3);
    estadoAnteriorSW3 = lectura;
    return pulsado;
} 
