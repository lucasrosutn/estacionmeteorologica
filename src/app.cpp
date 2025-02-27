#include "app.h"
#include "sensor_dht22.h"
#include "display.h"
#include "sensor_bmp180.h"
#include "wifi_.h"
#include "publish.h"
#include "mqtt.h"
#include "config.h"
#include "led.h"
#include "storage.h"
#include "serial_commands.h"


extern Config config;

Storage storage;

//--Local variables
bool wifi_state;

float temperature = 0;
float humidity = 0;
float pressure = 0;
float altitude = 0;

// Executes the app main logic loop
void runApp() {
    // Actualiza las lecturas del DHT22 (esto actualiza el buffer de 5 muestras)
    
    updateDHT22();
    
    // Obtiene los valores promediados de temperatura y humedad
    temperature = getAverageTemperature();
    humidity = getAverageHumidity();
    
    // Lee los demás sensores
    pressure = readPress();
    altitude = readAlt();
    
    // Parpadea el LED según los valores leídos
    blink_led(LED_PIN, temperature, humidity);
    
    // Verifica si se produjo un error en la lectura del DHT22
    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Error while reading DHT sensor!");
    }
    
    // Muestra los datos en el display OLED
    mostrarDatos(temperature, humidity, pressure);
    
    // Publica los datos
    publishTemperature(temperature);
    publishHumidity(humidity);
    publishPressure(pressure);
    publishAltitude(altitude);

    // --- Nuevo código: Control del LED único basado en ambas condiciones ---
    // El LED se enciende solo si la temperatura y la humedad superan sus respectivos umbrales.
    if (temperature > storage.getTempThreshold() && humidity > storage.getHumThreshold()) {
        digitalWrite(LED_PIN, HIGH);
    } else {
        digitalWrite(LED_PIN, LOW);
    }
    // --- Fin del nuevo código ---
    
    // Llama al loop del wifi (si corresponde)
    wifi_state = wifi_loop();
    // Verifica si hay nuevos comandos desde el puerto serie
    checkSerialCommands(storage);

    delay(2000); // Espera 2 segundos antes de refrescar
}
