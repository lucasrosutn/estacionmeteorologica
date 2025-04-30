#ifndef SENSOR_H
#define SENSOR_H

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "config.h"
#include <Arduino.h>
#include <math.h>

#define DHT_PIN 4 // sets pin in use
#define DHT_TYPE DHT22


// Initializes DHT22 sensor
void initSensor();

// refreshes lecture from the sensor (every 2 seconds)
void updateDHT22();

// Gets average temperature from the last 10 readings
float getAverageTemperature();

// Gets average relative humidity from the last 10 readings
float getAverageHumidity();


#endif // SENSOR_H
