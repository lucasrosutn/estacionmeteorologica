#include "sensor_dht22.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <math.h>  // Para isnan()

// number of samples for the mean value (SP: promedio)
#define NUM_MUESTRAS 10

// bufffers to storage the last readings
static float tempBuffer[NUM_MUESTRAS];
static float humBuffer[NUM_MUESTRAS];
static uint8_t bufferIndex = 0;
static bool bufferLleno = false;

DHT dht(DHT_PIN, DHT_TYPE);

// Initializes DHT22 sensor
void initSensor() {
    dht.begin();
}

// auxiliar functin to calculate the mean (SP: promedio)
static float calcularPromedio(const float datos[], uint8_t cantidad) {
    float suma = 0.0;
    for (uint8_t i = 0; i < cantidad; i++) {
      suma += datos[i];
    }
    return suma / cantidad;
}

// actualizes the buffers every 2 seconds
void updateDHT22() {
    // gets temperature and huidity
    float temperatura = dht.readTemperature();
    float humedad = dht.readHumidity();  

    // checks if the readings are valid (numbers)
    if (isnan(temperatura) || isnan(humedad)) {
      // message in case the reading fails (not a number)
      Serial.println("Error al leer el DHT22");
      return;
    }

    // Storage lectures on the buffer
    tempBuffer[bufferIndex] = temperatura;
    humBuffer[bufferIndex] = humedad;
   
    // refreshes the index in a circular way
    bufferIndex++;
    if (bufferIndex >= NUM_MUESTRAS) {
      bufferIndex = 0;
      bufferLleno = true;
    }
}

// Gets the mean value (SP:promedio) from the las readings of temperature
float getAverageTemperature() {
    uint8_t cantidadMuestras = bufferLleno ? NUM_MUESTRAS : bufferIndex;
    if (cantidadMuestras == 0) {
      return NAN; // Aún no hay datos suficientes
    }
    return calcularPromedio(tempBuffer, cantidadMuestras);
}

// Gets the mean value (SP:promedio) from the las readings of relative humidity
float getAverageHumidity() {
    uint8_t cantidadMuestras = bufferLleno ? NUM_MUESTRAS : bufferIndex;
    if (cantidadMuestras == 0) {
      return NAN;
    }
    return calcularPromedio(humBuffer, cantidadMuestras);
}

// Reads temperature from DHT22 sensor (raw value)
float readTemperature() {
    return dht.readTemperature(); // gives back temprature in celcius degrees
}

// Reads relative humidity from DHT22 sensor (valor crudo)
float readHumidity() {
    return dht.readHumidity(); // gives back relative humidity in percentage %
}