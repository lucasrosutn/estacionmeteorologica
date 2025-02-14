#include <Arduino.h>
#include <WiFi.h>
#include "setup.h"
#include "sensor_dht22.h"
#include "display.h"
#include "sensor_bmp180.h"
#include "config.h"
#include "wifi_.h"

Config config;


// Configurates the system initializing the necesary modules 
void setupSystem() {
    Serial.begin(19200);    // Initializes serial communication for debugging
    initSensor();           // Initilizes DHT22 sensor
    initDisplay();          // Initializes OLED display
    oled88_bienvenida();
    initBMP180();           // Initializes BMP180 sensor
    setupMQTT();            // Initializes mqtt 
    
 //--Init wifi
    config.ssid="DIDI_RULZ";
    config.ssid_pass="0041685240";
    config.ap_ssid=config.device;
    config.ap_pass="12345678";
    wifi_init(WIFI_AP_STA);
    reconnectMQTT();

}