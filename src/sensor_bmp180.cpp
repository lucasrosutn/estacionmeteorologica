#include "sensor_bmp180.h"

// Instancia global del sensor BMP180
Adafruit_BMP085 bmp;

void initBMP180() {
  if (!bmp.begin()) {
	  Serial.println("Could not find a valid BMP180 sensor, check wiring!");
  }else{
    Serial.println("Find BMP180!");
  }
}

float readPress(void) {
    return bmp.readPressure() / 100.0F; // Convierte a hPa
}

float readTemp(void) {
    return bmp.readTemperature();
}

float readAlt(void){
    return bmp.readAltitude();
}