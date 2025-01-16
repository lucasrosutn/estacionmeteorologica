#include "app.h"
#include "sensor_dht22.h"
#include "display.h"
#include "sensor_bmp180.h"


float temperature=0;
float humidity=0;
float pressure=0;

// Ejecuta el ciclo lógico principal de la aplicación
void runApp() {
    temperature = readTemperature(); // Lee la temperatura del sensor DHT22
    humidity = readHumidity();         // Lee la humedad del sensor DHT22
    pressure = readPress();
    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Error al leer del sensor DHT!");
    }
    mostrarDatos(temperature, humidity, pressure);   // Muestra los datos en el display OLED
    Serial.print("Altitude = ");
    Serial.print(readAlt());
    Serial.println(" meters");
    delay(2000);                          // Espera 2 segundos antes de la próxima actualización
}
