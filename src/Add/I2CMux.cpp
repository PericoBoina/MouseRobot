#include "Add/I2CMux.h"
#include <Wire.h>
#include <Arduino.h>


I2CMux::I2CMux(uint8_t devAddr) {
    i2cAddr = devAddr;
}

void I2CMux::selectChannel(uint8_t x) {
    Wire.beginTransmission(i2cAddr);
    Wire.write(1 << x);
    Wire.endTransmission();
}

void I2CMux::scanner()
{
    Serial.println("--TCA9548--");
    for (uint8_t t = 0; t < 8; t++)
    {
        selectChannel(t);
        Serial.print("Salida: ");
        Serial.println(t);
        for (uint8_t addr = 0; addr <= 127; addr++)
        {
            if (addr == i2cAddr)
                continue;
            Wire.beginTransmission(addr);
            if (Wire.endTransmission() == 0)
            {
                Serial.print("0x");
                Serial.println(addr, HEX);
            }
        }
        delay(1000);
    }
}
