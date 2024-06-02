#ifndef LED_H
#define LED_H

class Led {
public:
    Led();
    void init();
    void turnOn(int ledNumber);
    void turnOff(int ledNumber);
    void show();
};

#endif // LED_H