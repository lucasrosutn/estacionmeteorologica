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
        delay(500);
        digitalWrite(led_pin, LOW);
        delay(500);
    } else {
        digitalWrite(led_pin, LOW);  // turns off the led if the condition it's not met. 
    }
}