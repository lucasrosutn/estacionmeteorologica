#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include "config.h"


void welcome(void);
void blink_led(uint8_t led_pin, float temperature, float humidity);

#endif
