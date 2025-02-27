#ifndef STORAGE_H
#define STORAGE_H

#include <Preferences.h>

class Storage {
public:
  Storage();
  void begin();
  // Getters
  float getTempThreshold();
  float getHumThreshold();
  String getSSID();
  String getPassword();
  String getBrokerIP();
  // Setters
  void setTempThreshold(float value);
  void setHumThreshold(float value);
  void setSSID(const String &ssid);
  void setPassword(const String &password);
  void setBrokerIP(const String &ip);
  // ends preferences session
  void end();
  
private:
  Preferences preferences;
};

#endif
