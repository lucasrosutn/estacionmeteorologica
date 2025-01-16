#ifndef SENSOR_H
#define SENSOR_H

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "config.h"

// Initializes DHT22 sensor
void initSensor();

// Reads temperature in celcius degrees
float readTemperature();

// Reads relative humidity in %
float readHumidity();

#endif // SENSOR_H
