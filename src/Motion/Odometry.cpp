#include "Motion/Odometry.h"
#include "Sensors/Encoders.h"

Odometry::Odometry() : encoders(), lastEncoderPos_L(0), lastEncoderPos_R(0),
                       distanciaEntreRuedas_mm(55), ticksPorMilimetro(50), x(0.0), y(0.0), theta(0.0)
{
    encoders.init();
}

void Odometry::update()
{

    int EncoderPos_L = encoders.getCount(1);
    int EncoderPos_R = encoders.getCount(2);
    int deltaEncoderPos_L = EncoderPos_L - lastEncoderPos_L;
    int deltaEncoderPos_R = EncoderPos_R - lastEncoderPos_R;
    float distance_L = deltaEncoderPos_L / (float)ticksPorMilimetro;
    float distance_R = deltaEncoderPos_R / (float)ticksPorMilimetro;
    float delta_theta = (distance_R - distance_L) / distanciaEntreRuedas_mm;
    float distance = (distance_L + distance_R) / 2.0;
    x += distance * cos(theta);
    y += distance * sin(theta);
    theta += delta_theta;
    theta = atan2(sin(theta), cos(theta));
    lastEncoderPos_L = EncoderPos_L;
    lastEncoderPos_R = EncoderPos_R;
    Serial.print("Posición (x, y): ");
    Serial.print(x);
    Serial.print(" mm, ");
    Serial.print(y);
    Serial.print(" mm Orientación (theta): ");
    Serial.print(theta * 180.0 / PI);
    Serial.println(" grados");
    delay(1);
}
