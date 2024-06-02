#ifndef SENSOR_H
#define SENSOR_H

#include "Sensors/MPU6050_light.h"
#include "Sensors/VL53L0X.h"
#include "Add/I2CMux.h"
#include "Wire.h"

#define NUM_READINGS 10
#define DIST_THRESHOLD 125

#define ofsetGyro 9.58
#define NUM_SAMPLES 15 

class Sensor
{

public:
    Sensor();
    void init();
    void raw_distances();
    int left();
    int center();
    int right();
    int wall();
    float angleZ();
    void resetAngleZ();


private:
    VL53L0X sensor[3];
    I2CMux mux;
    MPU6050 mpu;
    void updateReadings(int leftDistance, int centerDistance, int rightDistance);
    int createState();
    int getAverageDistance(const int readings[], int numReadings);
    int leftReadings[NUM_READINGS];
    int centerReadings[NUM_READINGS];
    int rightReadings[NUM_READINGS];
    int  leftIndex;
    int centerIndex;
    int rightIndex;
    unsigned long lastUpdateTime;
    const int numLecturas = 10;
    const uint16_t delayTime = 10;
    float promedio = 0;
    float gyroReadings[NUM_SAMPLES] = {0};
    float angle = 0.0;
    float correction = 0.0; // Valor de corrección
};

#endif
