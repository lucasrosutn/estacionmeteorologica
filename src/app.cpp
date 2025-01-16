#include "app.h"
#include "sensor_dht22.h"
#include "display.h"
#include "sensor_bmp180.h"


float temperature=0;
float humidity=0;
float pressure=0;

// Executes the app main logic loop
void runApp() {
    temperature = readTemperature(); // reads temperature from DHT22 sensor
    humidity = readHumidity();         // reads humidity from DHT22 sensor
    pressure = readPress();
    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Error while reading DHT sensor!");
    }
    mostrarDatos(temperature, humidity, pressure);   // Shows data on the OLED display
    Serial.print("Altitude = ");
    Serial.print(readAlt());
    Serial.println(" meters");
    delay(2000);                          // Waits 2 seconds before refreshing
}
