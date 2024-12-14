#include "app.h"
#include "sensor_dht22.h"
#include "display.h"
#include "sensor_bmp180.h"


float temperatura=0;
float humedad=0;
float presion=0;

// Ejecuta el ciclo lógico principal de la aplicación
void runApp() {
    temperatura = readTemp(); // Lee la temperatura del sensor DHT22
    humedad = leerHumedad();         // Lee la humedad del sensor DHT22
    presion = readPress();
    if (isnan(temperatura) || isnan(humedad)) {
        Serial.println("Error al leer del sensor DHT!");
    }
    mostrarDatos(temperatura, humedad, presion);   // Muestra los datos en el display OLED
    Serial.print("Altitude = ");
    Serial.print(readAlt());
    Serial.println(" meters");
    delay(2000);                          // Espera 2 segundos antes de la próxima actualización
}
