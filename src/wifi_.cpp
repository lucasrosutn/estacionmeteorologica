
#include <Arduino.h>
#include <WiFi.h>
#include "wifi_.h"


//--Local variables
uint32_t _wifi_crono;
uint8_t _wifi_state = RECONNECT;
uint8_t _wifi_last_state = DISCONNECTED;
uint8_t _try_wifi_reconn=1;
bool _flag_wifi_reconnected=0;
bool _ap_state;

//--Extern variables
extern Config config;

//--Init and connect wifi network
bool wifi_init(WiFiMode_t mode){    
    WiFi.persistent(false);
    WiFi.mode(mode);
    WiFi.setAutoConnect(false);
    WiFi.setAutoReconnect(false);
    WiFi.disconnect();

    //--WiFi mode
    switch (mode){
        case WIFI_AP_STA:
            _APconnect();
            _wifi_state=_connect();
            break;
        case WIFI_AP:
            _APconnect();
            break;
        case WIFI_STA:
            _wifi_state=_connect();
            break;
        default:
            break;
    }
    if (_wifi_state==CONNECTED){
        return true;
    }else{
        return false;
    }
}

//--FMS for maintain wifi connection. Return state of connection (T/F)
bool wifi_loop(void){
  switch (_wifi_state){
    case CONNECTED:
      if (_get_wifi_status()!=CONNECTED){
        _wifi_state=DISCONNECTED;
      }
      break;

    case RECONNECT:
        Serial.print(F("WiFi reconnect "));
        Serial.println(_try_wifi_reconn);
        _try_wifi_reconn++;
        WiFi.begin(config.ssid,config.ssid_pass);
        _wifi_crono = millis();
        _wifi_state=WAITFORCONNECT;
        break;

    case DISCONNECTED:
        if(_get_wifi_status()!=CONNECTED){
          WiFi.disconnect();
          _wifi_crono = millis();
          _wifi_state=RECONNECT;
          _flag_wifi_reconnected=1;
        }else{
          _wifi_state=CONNECTED;
        }
        break;

    case WAITTORECONNECT:
      if (millis() - _wifi_crono >= RECONN_TIMEOUT){
        _wifi_state=RECONNECT;
      }
      break;

    case WAITFORCONNECT:
      if(_get_wifi_status()!=CONNECTED){
        if (millis() - _wifi_crono >= WAITFORCONNECT_TIMEOUT){
          _wifi_crono = millis();
          _wifi_state=WAITTORECONNECT;
        }
      }else{
         if(_flag_wifi_reconnected){
          Serial.println(F("WiFi reconnected!!"));
          _try_wifi_reconn=0;
          _flag_wifi_reconnected=0;
        }
        _wifi_state=CONNECTED;
      }
      break;

    default:
      break;
  }
  
  if (_wifi_state==CONNECTED){
    return true;
  }else{
    return false;
  }
}




//--Connect to wifi network. Return state of connection (T/F)
bool _connect(void){
  Serial.printf("Connecting to %s with %s password", config.ssid, config.ssid_pass);
  //WiFi.begin("MAC_E","wpaadministrator08");
  WiFi.begin(config.ssid, config.ssid_pass);
  _wifi_crono = millis();
  while (WiFi.status()!=WL_CONNECTED){
    Serial.print(F("."));
    delay(100);
    if (millis() - _wifi_crono >= WAITFORCONNECT_TIMEOUT){
      break;
    }
  }
  Serial.println("");
  _wifi_state=_get_wifi_status();
  _wifi_crono = millis();
  if (_wifi_state==CONNECTED){
    Serial.printf("Connected to %s with IP: ", config.ssid);
    Serial.println(WiFi.localIP());
    return true;
  }else{
      Serial.println("Not connected!");
    return false;
  }
}


//--Get the wifi state for state machine. Return state (see FSM_WIFI_STATES enum in wifi.h)
uint8_t _get_wifi_status(void){
  switch (WiFi.status()){
    case WL_CONNECTED:
      if(WiFi.localIP()[3]==0){ //check if have ip number (Fail terterbio01)
        return DISCONNECTED;
      }
      return CONNECTED;
      break;
    case WL_IDLE_STATUS:
      return WAITFORCONNECT;
      break;
    case WL_NO_SSID_AVAIL:
    case WL_CONNECT_FAILED:
    case WL_CONNECTION_LOST:
    case WL_DISCONNECTED: 
      return DISCONNECTED;
      break;
    default:
      return DISCONNECTED;
      break;
  }
}

//--Access Point init 
void _APconnect(void){
  _ap_state=WiFi.softAP(config.ap_ssid, config.ap_pass);
  if (_ap_state){
    Serial.print("AP ready with IP: ");
    Serial.println(WiFi.softAPIP());
  }else{
    Serial.println("AP init faill");  
  }
}