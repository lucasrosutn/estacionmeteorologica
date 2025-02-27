#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include "config.h"


void welcome(void); //welcome blik routine
void blink_led(uint8_t led_pin, float temperature, float humidity); //blinks led when temp & hum are above certain values

#endif
