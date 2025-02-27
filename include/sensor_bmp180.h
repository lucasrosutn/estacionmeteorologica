#ifndef SENSOR_BMP180_H
#define SENSOR_BMP180_H

#include <Adafruit_BMP085.h>

void initBMP180();      // Initializes BMP180 sensor

//gets values from the sensor
float readPress(void);
float readTemp(void);
float readAlt(void);

#endif
