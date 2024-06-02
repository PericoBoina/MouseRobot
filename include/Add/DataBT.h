#ifndef DATABT_H
#define DATABT_H

#include <Arduino.h>
#include <BluetoothSerial.h>

class DataBT
{
public:
    DataBT();
    void updatePID();
    float getP() const;
    float getI() const;
    float getD() const;
    float getV() const;

private:
    BluetoothSerial SerialBT;
    float P, I, D, V;
    void parseData(String data);
};

#endif
