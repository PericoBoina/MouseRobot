#include <Arduino.h>
#include <Add/Led.h>
#include <Add/Buttons.h>
#include <Add/I2CMux.h>
#include <Add/DataBT.h>
#include <Add/MadgwickAHRS.h>
#include <Motion/MotorController.h>
#include <Motion/Motion.h>
#include <Sensors/Sensor.h>
#include <Sensors/Encoders.h>
#include <Sensors/MPU6050_light.h>
#include <BluetoothSerial.h>

I2CMux mux(0x70);
Sensor sensor;
Encoders enc;
Led led;
MotorController motor;
Buttons button;
BluetoothSerial SerialBT;
DataBT dataBT;
MPU6050 mpu(Wire);
Motion move;



void setup()
{
  Serial.begin(115200);
  Wire.begin(21, 22);
  SerialBT.begin("MouseRobot");
  sensor.init();
  button.init();
  motor.init();
  enc.init();
  led.init();
  led.show();
}

void loop()
{
  move.Straight();
}