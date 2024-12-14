#include "sensor_dht22.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHT_PIN 4 // Cambia al pin que estás usando
#define DHT_TYPE DHT22

DHT dht(DHT_PIN, DHT_TYPE);


// Inicializa el sensor DHT22
void initSensor() {
    dht.begin();
}

// Lee la temperatura del sensor DHT22
float leerTemperatura() {
    return dht.readTemperature(); // Devuelve la temperatura en grados Celsius
}

// Lee la humedad relativa del sensor DHT22
float leerHumedad() {
    return dht.readHumidity(); // Devuelve la humedad relativa en porcentaje
}
