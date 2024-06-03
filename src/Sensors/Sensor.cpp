#include "Sensors/Sensor.h"
#include "Wire.h"
#include "Add/Led.h"

Sensor::Sensor() : mux(0x70), leftIndex(0), centerIndex(0), rightIndex(0),
                   mpu(Wire) {}

//////////////////////////////////////////////////////////////////////////////////////

void Sensor::init()
{
    for (int i = 0; i < 3; ++i)
    {
        mux.selectChannel(i);
        sensor[i].setTimeout(500);
        if (!sensor[i].init())
        {
            Serial.print("Failed sensor ");
            Serial.println(i);
            while (true)
            {
            }
        }
        sensor[i].startContinuous();
    }
    mux.selectChannel(3);
    byte status = mpu.begin();
    Serial.print(F("MPU6050 status: "));
    Serial.println(status);
    while (status != 0)
    {
    }
    Serial.println(F("Calculating offsets, do not move MPU6050"));
    delay(1000);
    mpu.calcOffsets();
    Serial.println("Done!\n");
}

//////////////////////////////////////////////////////////////////////////////////////

void Sensor::update(float sensorValues[])
{
    float d[4]; // Almacena los valores temporales
    for (int i = 0; i < 4; ++i)
    {
        switch (i)
        {
        case 0:
            mux.selectChannel(1);
            d[0] = sensor[1].readRangeContinuousMillimeters();
            break;
        case 1:
            mux.selectChannel(2);
            d[1] = sensor[2].readRangeContinuousMillimeters();
            break;
        case 2:
            mux.selectChannel(0);
            d[2] = sensor[0].readRangeContinuousMillimeters();
            break;
        case 3:
            mux.selectChannel(3);
            mpu.update();
            d[3] = mpu.getAngleZ();
            break;
        }
    }
    for (int i = 0; i < 4; ++i)
    {
        sensorValues[i] = d[i];
    }
}

/*
    ----- Example -----

  float sensorValues[4];
  sensor.update(sensorValues);
  float D1 = sensorValues[0];
  float D2 = sensorValues[1];
  float D3 = sensorValues[2];
  float Az = sensorValues[3];
  Serial.print("D1:");
  Serial.print(D1);
  Serial.print(" -- ");
  Serial.print("D2:");
  Serial.print(D2);
  Serial.print(" -- ");
  Serial.print("D3:");
  Serial.print(D3);
  Serial.print(" -- ");
  Serial.print("Z:");
  Serial.println(Az);
*/

//////////////////////////////////////// Lectura paredes ///////////////////////////////////////

// Estado:
//   0   ->  Ninguna pared detectada.
//   1   ->  Solo la pared derecha detectada.
//   2   ->  Solo la pared central detectada.
//   3   ->  Paredes central y derecha detectadas.
//   4	 ->  Solo la pared izquierda detectada.
//   5	 ->  Paredes izquierda y derecha detectadas.
//   6	 ->  Paredes izquierda y central detectadas.
//   7	 ->  Paredes izquierda, central y derecha detectadas.

int Sensor::wall()
{
    float sensorValues[4];
    update(sensorValues);
    float D1 = sensorValues[0];
    float D2 = sensorValues[1];
    float D3 = sensorValues[2];
    int leftDistance = D1;
    int centerDistance = D2;
    int rightDistance = D3;
    updateReadings(leftDistance, centerDistance, rightDistance);
    return createState();
}

void Sensor::updateReadings(int leftDistance, int centerDistance, int rightDistance)
{
    leftReadings[leftIndex] = leftDistance;
    centerReadings[centerIndex] = centerDistance;
    rightReadings[rightIndex] = rightDistance;
    leftIndex = (leftIndex + 1) % NUM_READINGS;
    centerIndex = (centerIndex + 1) % NUM_READINGS;
    rightIndex = (rightIndex + 1) % NUM_READINGS;
}

int Sensor::createState()
{
    int avgLeftDistance = getAverageDistance(leftReadings, NUM_READINGS);
    int avgCenterDistance = getAverageDistance(centerReadings, NUM_READINGS);
    int avgRightDistance = getAverageDistance(rightReadings, NUM_READINGS);
    int state = 0;
    state |= (avgLeftDistance < DIST_THRESHOLD) ? (1 << 2) : 0;
    state |= (avgCenterDistance < DIST_THRESHOLD) ? (1 << 1) : 0;
    state |= (avgRightDistance < DIST_THRESHOLD) ? (1 << 0) : 0;
    return state;
}

int Sensor::getAverageDistance(const int readings[], int numReadings)
{
    int sum = 0;
    for (int i = 0; i < numReadings; ++i)
    {
        sum += readings[i];
    }
    return sum / numReadings;
}

//////////////////////////////////////////////////////////////////////////////////////
