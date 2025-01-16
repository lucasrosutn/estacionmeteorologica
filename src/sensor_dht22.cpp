#include "sensor_dht22.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHT_PIN 4 // Cambia al pin que estás usando
#define DHT_TYPE DHT22

DHT dht(DHT_PIN, DHT_TYPE);


// Initializes DHT22 sensor
void initSensor() {
    dht.begin();
}

// Reads temperature from DHT22 sensor
float readTemperature() {
    return dht.readTemperature(); // Gives temperature in celcius degrees
}

// Reads relative humidity from DHT22 sensor
float readHumidity() {
    return dht.readHumidity(); // Gives relative humidity in %
}
