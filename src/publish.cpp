#include "publish.h"

//AJUSTAR TOPICOS Y DEMAS

void publishTemperature(float temperature) {
    String payload = String(temperature);
    if (mqttClient.publish("smartvent/temperature", payload.c_str())){
        Serial.println("Publish successfull");
    }else{
        Serial.println("Publish not successfull");
    }
}

void publishHumidity(float humidity) {
    String payload = String(humidity);
    if (mqttClient.publish("smartvent/humidity", payload.c_str())){
        Serial.println("Publish successfull");
    }else{
        Serial.println("Publish not successfull");
    }
}


