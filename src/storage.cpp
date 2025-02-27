#include "storage.h"

Storage::Storage() {
  // Constructor vacío; la inicialización se hará en begin()
}

void Storage::begin() {
  // Abrimos el espacio de nombres "config" en modo lectura/escritura
  preferences.begin("config", false);
}

float Storage::getTempThreshold() {
  return preferences.getFloat("tempTh", 24.0);  // Valor por defecto: 24°C
}

float Storage::getHumThreshold() {
  return preferences.getFloat("humTh", 50.0);   // Valor por defecto: 50%
}

String Storage::getSSID() {
  return preferences.getString("ssid", "DIDI_RULZ");
}

String Storage::getPassword() {
  return preferences.getString("pass", "0041685240");
}

String Storage::getBrokerIP() {
  return preferences.getString("broker", "192.168.1.100");
}

void Storage::setTempThreshold(float value) {
  preferences.putFloat("tempTh", value);
}

void Storage::setHumThreshold(float value) {
  preferences.putFloat("humTh", value);
}

void Storage::setSSID(const String &ssid) {
  preferences.putString("ssid", ssid);
}

void Storage::setPassword(const String &password) {
  preferences.putString("pass", password);
}

void Storage::setBrokerIP(const String &ip) {
  preferences.putString("broker", ip);
}

void Storage::end() {
  preferences.end();
}
