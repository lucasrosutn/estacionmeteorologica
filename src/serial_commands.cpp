#include "serial_commands.h"

void checkSerialCommands(Storage &storage) {
  if (Serial.available() > 0) {
    // reads the whole last line and erases blank spaces
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command.startsWith("T=")) {
      // refreshes the temperature threshold
      String valueStr = command.substring(2);
      float newTemp = valueStr.toFloat();
      storage.setTempThreshold(newTemp);
      Serial.print("Nuevo umbral de temperatura: ");
      Serial.println(newTemp);
    } 
    else if (command.startsWith("H=")) {
      // refreshes relative humidty threshold
      String valueStr = command.substring(2);
      float newHum = valueStr.toFloat();
      storage.setHumThreshold(newHum);
      Serial.print("Nuevo umbral de humedad: ");
      Serial.println(newHum);
    } 
    else if (command.startsWith("S=")) {
      // refreshes SSID
      String newSSID = command.substring(2);
      storage.setSSID(newSSID);
      Serial.print("Nuevo SSID: ");
      Serial.println(newSSID);
    } 
    else if (command.startsWith("P=")) {
      // refreshes password
      String newPass = command.substring(2);
      storage.setPassword(newPass);
      Serial.print("Nueva password: ");
      Serial.println(newPass);
    } 
    else if (command.startsWith("B=")) {
      // refreshes broker IP
      String newBroker = command.substring(2);
      storage.setBrokerIP(newBroker);
      Serial.print("Nuevo broker IP: ");
      Serial.println(newBroker);
    } 
    else if (command.equalsIgnoreCase("SHOW")) {
      // shows actual configuration
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
