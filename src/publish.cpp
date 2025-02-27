#include "publish.h"

void publishTemperature(float temperature) {
    String payload = String(temperature);
    if (mqttClient.publish("estacionmeteorologica/temperature", payload.c_str())){
        Serial.println("Publish successfull");
    }else{
        Serial.println("Publish not successfull");
    }
}

void publishHumidity(float humidity) {
    String payload = String(humidity);
    if (mqttClient.publish("estacionmeteorologica/humidity", payload.c_str())){
        Serial.println("Publish successfull");
    }else{
        Serial.println("Publish not successfull");
    }
}

void publishPressure(float pressure) {
    String payload = String(pressure);
    if (mqttClient.publish("estacionmeteorologica/pressure", payload.c_str())){
        Serial.println("Publish successfull");
    }else{
        Serial.println("Publish not successfull");
    }
}

void publishAltitude(float altitude) {
    String payload = String(altitude);
    if (mqttClient.publish("estacionmeteorologica/altitude", payload.c_str())){
        Serial.println("Publish successfull");
    }else{
        Serial.println("Publish not successfull");
    }
}

