#ifndef _I2CMux_H
#define _I2CMux_H

#include <Wire.h>

class I2CMux
{
public:
    I2CMux(uint8_t devAddr);
    void selectChannel(uint8_t p);
    void scanner();

private:
    uint8_t i2cAddr;
};

#endif