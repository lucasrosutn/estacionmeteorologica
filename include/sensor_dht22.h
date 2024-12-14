#ifndef SENSOR_H
#define SENSOR_H

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "config.h"

// Inicializa el sensor DHT22
void initSensor();

// Lee la temperatura en grados Celsius
float leerTemperatura();

// Lee la humedad relativa en porcentaje
float leerHumedad();

#endif // SENSOR_H
