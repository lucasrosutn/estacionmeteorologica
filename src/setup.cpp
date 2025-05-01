#include <Arduino.h>
#include <WiFi.h>
#include "setup.h"
#include "sensor_dht22.h"
#include "display.h"
#include "sensor_bmp180.h"
#include "config.h"
#include "wifi_.h"
#include "storage.h"

Config config;
extern Storage storage;  // Reference to the global instance defined in app.cpp
uint32_t timetopublish;

// Configurates the system initializing the necesary modules 
void setupSystem() {
    Serial.begin(19200);    // Initializes serial communication for debugging
    initSensor();           // Initilizes DHT22 sensor
    initDisplay();          // Initializes OLED display
    oled88_bienvenida();
    initBMP180();           // Initializes BMP180 sensor
    pinMode(LED_PIN,OUTPUT);
    welcome();
    setupMQTT();            // Initializes mqtt 
 
    pinMode(LED_PIN, OUTPUT);

    storage.begin();
    float tempThreshold = storage.getTempThreshold();
    float humThreshold  = storage.getHumThreshold();
    config.ssid         = storage.getSSID();
    config.ssid_pass     = storage.getPassword();
    config.broker_ip    = storage.getBrokerIP();
    
    
    // Prints the config to verify if it has been loaded succesfully
    Serial.println("Configuración cargada desde NVS:");
    Serial.print("Temp Threshold: "); Serial.println(tempThreshold);
    Serial.print("Hum Threshold: "); Serial.println(humThreshold);
    Serial.print("SSID: "); Serial.println(config.ssid);
    Serial.print("Password: "); Serial.println(config.ssid_pass);
    Serial.print("Broker IP: "); Serial.println(config.broker_ip);
  

    //--Init wifi

    wifi_init(WIFI_AP_STA);
    reconnectMQTT();
    timetopublish=millis();
}

