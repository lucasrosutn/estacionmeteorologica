#include "app.h"
#include "sensor_dht22.h"
#include "display.h"
#include "sensor_bmp180.h"
#include "wifi_.h"
#include "publish.h"
#include "mqtt.h"
#include "config.h"
#include "led.h"



extern Config config;


//--Local variables
bool wifi_state;


float temperature=0;
float humidity=0;
float pressure=0;

// Executes the app main logic loop
void runApp() {
    temperature = readTemperature(); // reads temperature from DHT22 sensor
    humidity = readHumidity();         // reads humidity from DHT22 sensor
    pressure = readPress();
    blink_led(LED_PIN, temperature, humidity);
    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Error while reading DHT sensor!");
    }
    mostrarDatos(temperature, humidity, pressure);   // Shows data on the OLED display

    //publishTemperature(temperature);
    //publishHumidity(humidity);
    // esto va aca?? el wifi_loop --> entiendo que si BORRAR LUEGO ***************************************************
    //wifi_state=wifi_loop();
    delay(2000);                          // Waits 2 seconds before refreshing

    
}
