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

    // refreshes the readings of the sensor to update and refresh the buffer
    updateDHT22();


    
   
    //gets the promediated values of temoerature and humidity
    temperature = getAverageTemperature();
    humidity = getAverageHumidity();
    

    // reads the values from bmp180 sensor, in charge of the values for pressure and altitude
    pressure = readPress();
    altitude = readAlt();
    


    // blinks led according to the values
    blink_led(LED_PIN, temperature, humidity);
    
    // verifies if an error occured while getting the readings from the dht22 sensor.
    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Error while reading DHT sensor!");
    }
    
    // shows data on the oled display
    mostrarDatos(temperature, humidity, pressure);
 
   
    // publishes data
    publish();

    
    //leds will only blink if temp and hum are above their respective threshold levels.
    if (temperature > storage.getTempThreshold() && humidity > storage.getHumThreshold()) {
        digitalWrite(LED_PIN, HIGH);
    } else {
        digitalWrite(LED_PIN, LOW);
    }
    
    // Calls the wifi loop
    wifi_state = wifi_loop();

    // checks if there are new commands coming from the serial port
    checkSerialCommands(storage);


}
