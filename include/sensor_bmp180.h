#ifndef SENSOR_BMP180_H
#define SENSOR_BMP180_H

#include <Adafruit_BMP085.h>

void initBMP180();      // Inicializa el sensor BMP180
float readPress(void);
float readTemp(void);
float readAlt(void);

#endif
