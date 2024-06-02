#include "Add/DataBT.h"

DataBT::DataBT() : P(0.0), I(0.0), D(0.0), V(0){
}

void DataBT::updatePID()
{
    if (SerialBT.available())
    {
        String data = SerialBT.readStringUntil('\n');
        parseData(data);
        }
}

void DataBT::parseData(String data)
{
    float idx1 = data.indexOf(',');
    float idx2 = data.indexOf(',', idx1 + 1);
    int idx3 = data.indexOf(',', idx2 + 1);
    if (idx1 == -1 || idx2 == -1 || idx3 == -1)
        return;
    P = data.substring(0, idx1).toFloat();
    I = data.substring(idx1 + 1, idx2).toFloat();
    D = data.substring(idx2 + 1, idx3).toFloat();
    V = data.substring(idx3 + 1).toInt();
}

float DataBT::getP() const {
    return P;
}

float DataBT::getI() const {
    return I;
}

float DataBT::getD() const {
    return D;
}

float DataBT::getV() const {
    return V;
}