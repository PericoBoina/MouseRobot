#include "Add/Led.h"

#include <Arduino.h>
#include "Add/Led.h"


#define LED_1 23
#define LED_2 25
#define LED_3 26
#define LED_4 27

Led::Led() {
}

void Led::init() {
    pinMode(LED_1, OUTPUT);
    pinMode(LED_2, OUTPUT);
    pinMode(LED_3, OUTPUT);
    pinMode(LED_4, OUTPUT);
}

void Led::turnOn(int ledNumber) {
    switch (ledNumber) {
    case 1:
        digitalWrite(LED_1, HIGH);
        break;
    case 2:
        digitalWrite(LED_2, HIGH);
        break;
    case 3:
        digitalWrite(LED_3, HIGH);
        break;
    case 4:
        digitalWrite(LED_4, HIGH);
        break;
    default:
        break;
    }
}

void Led::turnOff(int ledNumber) {
    switch (ledNumber) {
    case 1:
        digitalWrite(LED_1, LOW);
        break;
    case 2:
        digitalWrite(LED_2, LOW);
        break;
    case 3:
        digitalWrite(LED_3, LOW);
        break;
    case 4:
        digitalWrite(LED_4, LOW);
        break;
    default:
        break;
    }
}

void Led::show() {
    Serial.println("Starting show");
    for (int i = 1; i <= 5; i++) {
        turnOn(i);
        delay(200);
    }
    for (int i = 5; i >= 1; i--) {
        turnOff(i);
        delay(200);
    }
    Serial.println("Ending show");
}