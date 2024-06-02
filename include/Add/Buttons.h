#ifndef _BUTTONS_H_
#define _BUTTONS_H_

#include <Arduino.h>

class Buttons
{
public:
    void init();
    bool SW2();
    bool SW3();

private:
    const int SW2_PIN = 34;
    const int SW3_PIN = 35;
    bool estadoAnteriorSW2 = false;
    bool estadoAnteriorSW3 = false;
};

#endif