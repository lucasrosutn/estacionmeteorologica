#include <Arduino.h>
#include "setup.h"
#include "sensor_dht22.h"
#include "display.h"
#include "sensor_bmp180.h"


// Configura el sistema inicializando los módulos necesarios
void setupSystem() {
    Serial.begin(19200);    // Inicializa la comunicación serial para debugging
    initSensor();           // Inicializa el sensor DHT22
    initDisplay();          // Inicializa el display OLED
    oled88_bienvenida();
    initBMP180();           // Inicializa el sensor BMP180
    
}