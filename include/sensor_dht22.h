#ifndef SENSOR_H
#define SENSOR_H

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "config.h"
#include <Arduino.h>
#include <math.h>

#define DHT_PIN 4 // Cambia al pin que estás usando
#define DHT_TYPE DHT22


// Initializes DHT22 sensor
void initSensor();

// Actualiza la lectura del sensor (debe llamarse cada 2 segundos)
void updateDHT22();

// Obtiene la temperatura promedio de las últimas 5 lecturas
float getAverageTemperature();

// Obtiene la humedad promedio de las últimas 5 lecturas
float getAverageHumidity();


#endif // SENSOR_H
