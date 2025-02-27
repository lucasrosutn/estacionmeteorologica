#include "serial_commands.h"

void checkSerialCommands(Storage &storage) {
  if (Serial.available() > 0) {
    // Lee la línea completa hasta el salto de línea y quita espacios en blanco
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command.startsWith("T=")) {
      // Actualiza el umbral de temperatura
      String valueStr = command.substring(2);
      float newTemp = valueStr.toFloat();
      storage.setTempThreshold(newTemp);
      Serial.print("Nuevo umbral de temperatura: ");
      Serial.println(newTemp);
    } 
    else if (command.startsWith("H=")) {
      // Actualiza el umbral de humedad
      String valueStr = command.substring(2);
      float newHum = valueStr.toFloat();
      storage.setHumThreshold(newHum);
      Serial.print("Nuevo umbral de humedad: ");
      Serial.println(newHum);
    } 
    else if (command.startsWith("S=")) {
      // Actualiza el SSID
      String newSSID = command.substring(2);
      storage.setSSID(newSSID);
      Serial.print("Nuevo SSID: ");
      Serial.println(newSSID);
    } 
    else if (command.startsWith("P=")) {
      // Actualiza la password
      String newPass = command.substring(2);
      storage.setPassword(newPass);
      Serial.print("Nueva password: ");
      Serial.println(newPass);
    } 
    else if (command.startsWith("B=")) {
      // Actualiza el broker IP
      String newBroker = command.substring(2);
      storage.setBrokerIP(newBroker);
      Serial.print("Nuevo broker IP: ");
      Serial.println(newBroker);
    } 
    else if (command.equalsIgnoreCase("SHOW")) {
      // Muestra la configuración actual
      Serial.print("Temp Threshold: ");
      Serial.println(storage.getTempThreshold());
      Serial.print("Hum Threshold: ");
      Serial.println(storage.getHumThreshold());
      Serial.print("SSID: ");
      Serial.println(storage.getSSID());
      Serial.print("Password: ");
      Serial.println(storage.getPassword());
      Serial.print("Broker IP: ");
      Serial.println(storage.getBrokerIP());
    } 
    else {
      Serial.println("Comando desconocido.");
      Serial.println("Usa:");
      Serial.println("  T=<valor> para umbral de temperatura");
      Serial.println("  H=<valor> para umbral de humedad");
      Serial.println("  S=<valor> para SSID");
      Serial.println("  P=<valor> para password");
      Serial.println("  B=<valor> para broker IP");
      Serial.println("  SHOW para ver la configuración actual");
    }
  }
}
