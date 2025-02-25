#include "led.h"
#include "sensor_dht22.h"


void welcome(void){
    for(int i=0;i<5;i++){
        digitalWrite(LED_PIN,HIGH);
        delay(40);
        digitalWrite(LED_PIN,LOW);
        delay(40);
    }
    delay(500);
  }




  void blink_led(uint8_t led_pin, float temperature, float humidity) {
    if (temperature > 23.0 && humidity > 40.0) {  
        digitalWrite(led_pin, HIGH);
        delay(2000);
        digitalWrite(led_pin, LOW);
        delay(4000);
    } else {
        digitalWrite(led_pin, LOW);  // Apaga el LED si no cumple la condición
    }
}