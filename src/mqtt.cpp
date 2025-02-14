#include "mqtt.h"
#include <WiFi.h>

// AJUSTAR MIS DATOS DE SERV USER PASS + TOPIC Y PAYLOAD

#define MQTT_SERVER "192.168.1.5"
#define MQTT_PORT 1883
#define MQTT_USER "smartvent"
#define MQTT_PASSWORD "smartvent"


WiFiClient espClient;
PubSubClient mqttClient(espClient);

String topic_rpc_req;
String msg_rpc_req;

void setupMQTT() {
    mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
    mqttClient.setCallback(mqttCallback);
}


void reconnectMQTT() {
    
    while (!mqttClient.connected()) {
        Serial.println("Try to connect to MQTT server");
        if (mqttClient.connect("smartvent", MQTT_USER, MQTT_PASSWORD)) {
            Serial.println("Connected to MQTT server!");
            mqttClient.subscribe("smartvent/commands");
        } else {
            delay(5000);
        }
    }
}


void mqttCallback(char* topic, byte* payload, unsigned int length) {
    payload[length] = '\0';
    topic_rpc_req = String((char*)topic);
    msg_rpc_req = String((char*)payload);
    //--Debug de mensaje de entrada
    Serial.print("[DEBUG RPC] Topico de pregunta:");Serial.println(topic_rpc_req);
    Serial.print("[DEBUG RPC] Mensaje de pregunta:");Serial.println(msg_rpc_req);
}