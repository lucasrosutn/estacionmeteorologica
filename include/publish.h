#ifndef PUBLISH_H
#define PUBLISH_H


#include "mqtt.h" 
#include "setup.h"
#include "app.h"

void publishTemperature(float temperature);
void publishHumidity(float humidity);
void publishPressure(float pressure);
void publishAltitude(float altitude);
void publish(void);


#endif