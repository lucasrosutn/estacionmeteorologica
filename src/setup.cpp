#include <Arduino.h>
#include "setup.h"
#include "sensor_dht22.h"
#include "display.h"
#include "sensor_bmp180.h"


// Configurates the system initializing the necesary modules 
void setupSystem() {
    Serial.begin(19200);    // Initializes serial communication for debugging
    initSensor();           // Initilizes DHT22 sensor
    initDisplay();          // Initializes OLED display
    oled88_bienvenida();
    initBMP180();           // Initializes BMP180 sensor
    
}