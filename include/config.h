#ifndef CONFIG_H
#define CONFIG_H

// Pines de conexión
const int DHT_PIN = 4;         // Pin GPIO donde está conectado el sensor DHT22
const int OLED_RESET_PIN = -1; // Reset del OLED, -1 si no se usa

// Configuraciones del DHT
#define DHT_TYPE DHT22          // Tipo de sensor DHT utilizado

#endif // CONFIG_H
