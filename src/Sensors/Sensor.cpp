#include "Sensors/Sensor.h"
#include "Wire.h"
#include "Add/Led.h"


Sensor::Sensor() : mux(0x70), leftIndex(0), centerIndex(0), rightIndex(0),
                   lastUpdateTime(0), mpu(Wire) {}

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
    mpu.begin();
    mpu.calcGyroOffsets();
    for (int i = 0; i < NUM_SAMPLES; i++)
    {
        gyroReadings[i] = mpu.getAngleZ();
    }
}
//////////////////////////////////////////// MPU6050 ////////////////////////////////////////////

float Sensor::angleZ() {
    mux.selectChannel(3);
    mpu.update();
    for (int i = 0; i < NUM_SAMPLES - 1; i++) {
        gyroReadings[i] = gyroReadings[i + 1];
    }
    gyroReadings[NUM_SAMPLES - 1] = mpu.getAngleZ();
    float sum = 0;
    for (int i = 0; i < NUM_SAMPLES; i++) {
        sum += gyroReadings[i];
    }
    float average = sum / NUM_SAMPLES;
    angle = average - correction; 
    return angle;
}

void Sensor::resetAngleZ()
{
}

////////////////////////////////////// VL53L0X Sensors ///////////////////////////////////////////

int Sensor::left()
{
    mux.selectChannel(1);
    return sensor[1].readRangeContinuousMillimeters();
}

int Sensor::center()
{
    mux.selectChannel(2);
    return sensor[2].readRangeContinuousMillimeters();
}

int Sensor::right()
{
    mux.selectChannel(0);
    return sensor[0].readRangeContinuousMillimeters();
}

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
    int leftDistance = left();
    int centerDistance = center();
    int rightDistance = right();
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
