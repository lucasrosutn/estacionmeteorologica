#ifndef CONFIG_H
#define CONFIG_H

// conection pins
const int DHT_PIN = 4;         // GPIO pin where the dht22 sensor is connected
const int OLED_RESET_PIN = -1; // OLED reset, -1 if not in use

// dht configuration
#define DHT_TYPE DHT22          // Type of DHT sensor in use

#endif // CONFIG_H
