#include "sensor_bmp180.h"

// Global instance of the BMP180 sensor
Adafruit_BMP085 bmp;

void initBMP180() {
  if (!bmp.begin()) {
	  Serial.println("Could not find a valid BMP180 sensor, check wiring!");
  }else{
    Serial.println("Find BMP180!");
  }
}

float readPress(void) {
    return bmp.readPressure() / 100.0F; // Convertion to hPa
}

float readTemp(void) {
    return bmp.readTemperature();
}

float readAlt(void){
    return bmp.readAltitude();
}