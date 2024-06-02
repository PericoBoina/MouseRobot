#include <Arduino.h>
#include <Add/Led.h>
#include <Add/Buttons.h>
#include <Add/I2CMux.h>
#include <Add/DataBT.h>
#include <Motion/MotorController.h>
// #include <Motion/Motion.h>
#include <Sensors/Sensor.h>
#include <Sensors/Encoders.h>
#include <BluetoothSerial.h>
#include <Sensors/MPU6050_light.h>
#include <Add/MadgwickAHRS.h>

I2CMux mux(0x70);
Sensor sensor;
Encoders enc;
Led led;
MotorController motor;
Buttons button;
BluetoothSerial SerialBT;
DataBT dataBT;
//Motion move(enc, motor);
MPU6050 mpu(Wire);
Madgwick filter;

void setup()
{
  Wire.begin(21, 22);
  Serial.begin(115200);
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
  led.turnOn(2);
  mux.selectChannel(3);
  mpu.update();
  float ax = mpu.getAccX();
  float ay = mpu.getAccY();
  float az = mpu.getAccZ();
  float gx = mpu.getGyroX();
  float gy = mpu.getGyroY();
  float gz = mpu.getGyroZ();
  filter.updateIMU(gx, gy, gz, ax, ay, az);
  float roll = filter.getRoll();
  float pitch = filter.getPitch();
  float yaw = filter.getYaw();
  Serial.print("Roll: ");
  Serial.print(roll);
  Serial.print(" Pitch: ");
  Serial.print(pitch);
  Serial.print(" Yaw: ");
  Serial.println(yaw);
  delay(1);
}
