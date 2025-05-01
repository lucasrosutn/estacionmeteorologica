#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// conection pins
const int DHT_PIN = 4;         // GPIO pin where the dht22 sensor is connected
const int OLED_RESET_PIN = -1; // OLED reset, -1 if not in use

// dht configuration
#define DHT_TYPE DHT22          // Type of DHT sensor in use

//--Hardware PINS definitions

//#define ONBOARD_LED_PIN             2 ***VER SI VA ESTE O EL DE ABAJO***
#define LED_PIN                     2
//#define LED_Tmax  12   // Ejemplo: Pin para el LED de temperatura
//#define LED_HRmax 13   // Ejemplo: Pin para el LED de humedad

//--Structures
struct Config {
  String device;
  String ssid;
  String ssid_pass;
  String ap_ssid;
  String ap_pass;
  String broker_ip;
};

#endif // CONFIG_H

