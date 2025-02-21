#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// conection pins
const int DHT_PIN = 4;         // GPIO pin where the dht22 sensor is connected
const int OLED_RESET_PIN = -1; // OLED reset, -1 if not in use

// dht configuration
#define DHT_TYPE DHT22          // Type of DHT sensor in use

//--Hardware PINS definitions

//#define ONBOARD_LED_PIN             2
#define LED_PIN                     2


//--Structures
struct Config {
  const char* device;
  const char* ssid;
  const char* ssid_pass;
  const char* ap_ssid;
  const char* ap_pass;
};

#endif // CONFIG_H
