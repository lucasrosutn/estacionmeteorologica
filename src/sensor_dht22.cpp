#include "sensor_dht22.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <math.h>  // Para isnan()

// Número de muestras para el promedio
#define NUM_MUESTRAS 10

// Buffers para almacenar las últimas lecturas
static float tempBuffer[NUM_MUESTRAS];
static float humBuffer[NUM_MUESTRAS];
static uint8_t bufferIndex = 0;
static bool bufferLleno = false;

DHT dht(DHT_PIN, DHT_TYPE);

// Initializes DHT22 sensor
void initSensor() {
    dht.begin();
}

// Función auxiliar para calcular el promedio
static float calcularPromedio(const float datos[], uint8_t cantidad) {
    float suma = 0.0;
    for (uint8_t i = 0; i < cantidad; i++) {
      suma += datos[i];
    }
    return suma / cantidad;
}

// Esta función se debe llamar cada 2 segundos para actualizar los buffers
void updateDHT22() {
    // Lee la temperatura y humedad
    float temperatura = dht.readTemperature();
    float humedad = dht.readHumidity();  

    // Verifica que las lecturas sean válidas
    if (isnan(temperatura) || isnan(humedad)) {
      // En caso de error, puedes decidir no actualizar o registrar el fallo
      Serial.println("Error al leer el DHT22");
      return;
    }

    // Almacena las lecturas en los buffers
    tempBuffer[bufferIndex] = temperatura;
    humBuffer[bufferIndex] = humedad;
   
    // Actualiza el índice de forma circular
    bufferIndex++;
    if (bufferIndex >= NUM_MUESTRAS) {
      bufferIndex = 0;
      bufferLleno = true;
    }
}

// Retorna el promedio de las últimas lecturas de temperatura
float getAverageTemperature() {
    uint8_t cantidadMuestras = bufferLleno ? NUM_MUESTRAS : bufferIndex;
    if (cantidadMuestras == 0) {
      return NAN; // Aún no hay datos suficientes
    }
    return calcularPromedio(tempBuffer, cantidadMuestras);
}

// Retorna el promedio de las últimas lecturas de humedad
float getAverageHumidity() {
    uint8_t cantidadMuestras = bufferLleno ? NUM_MUESTRAS : bufferIndex;
    if (cantidadMuestras == 0) {
      return NAN;
    }
    return calcularPromedio(humBuffer, cantidadMuestras);
}

// Reads temperature from DHT22 sensor (valor crudo)
float readTemperature() {
    return dht.readTemperature(); // Devuelve la temperatura en grados Celsius
}

// Reads relative humidity from DHT22 sensor (valor crudo)
float readHumidity() {
    return dht.readHumidity(); // Devuelve la humedad relativa en %
}