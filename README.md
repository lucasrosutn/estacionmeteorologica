# Estación Meteorológica con ESP32

## Descripción

Este proyecto consiste en el desarrollo de una estación meteorológica embebida basada en el microcontrolador ESP32. Permite medir temperatura, humedad relativa y presión atmosférica, publicando los datos en tiempo real mediante el protocolo MQTT hacia un broker remoto, sin almacenamiento local de los registros históricos. Además, incorpora persistencia de parámetros de configuración mediante el sistema de almacenamiento no volátil (NVS) del ESP32, permitiendo modificar valores de configuración de forma dinámica sin necesidad de recompilar el firmware.

El desarrollo fue realizado bajo un enfoque modular, orientado a facilitar la comprensión, el mantenimiento y la escalabilidad del código.

## Objetivos

- Implementar una arquitectura modular para adquisición de datos ambientales.
- Integrar sensores de temperatura, humedad y presión.
- Transmitir datos de mediciones mediante protocolo MQTT.
- Implementar almacenamiento de parámetros persistentes en NVS.
- Permitir la modificación de parámetros operativos mediante comandos por puerto serie.
- Documentar el proyecto de forma técnica para programadores.

## Materiales utilizados

### Hardware

- Placa de desarrollo ESP32 DevKit
- Sensor DHT22 (temperatura y humedad)
- Sensor BMP180 (presión atmosférica)
- Pantalla OLED 0.96" I2C (opcional, manejada mediante U8g2)
- Protoboard, cables y fuentes de alimentación

### Software

- Entorno de desarrollo: PlatformIO (Visual Studio Code)
- Lenguaje: C++
- Librerías utilizadas:
  - `Adafruit DHT Sensor Library` (v1.4.6)
  - `U8g2` (v2.34.18)
  - `Adafruit BMP085 Library` (v1.2.4)
  - `ArduinoJson` (v7.3.0)
  - `PubSubClient` (v2.8.0)

## Descripción general del sistema

El sistema se inicia configurando los periféricos de hardware, la conexión WiFi, la inicialización del cliente MQTT y la recuperación de parámetros persistentes desde la NVS. Posteriormente entra en un bucle principal donde realiza periódicamente las siguientes operaciones:

1. Lectura de sensores (DHT22 y BMP180).
2. Publicación de los datos adquiridos a través de MQTT.
3. Actualización de la pantalla OLED (si está habilitada).
4. Verificación de comandos entrantes por puerto serie para ajuste de parámetros.
5. Verificación de conexión WiFi y reconexión automática si es necesario.
6. Mantenimiento de la conexión MQTT activa.

## Descripción del código fuente

El proyecto está dividido en módulos funcionales claramente separados:

### main.cpp

- Inicializa el hardware general.
- Gestiona la conexión WiFi.
- Inicializa el sistema de persistencia mediante NVS.
- Configura el cliente MQTT.
- Controla el bucle principal de adquisición y publicación de datos.

### sensor_dht22.cpp / sensor_dht22.h

- Inicializa el sensor DHT22.
- Realiza las lecturas de temperatura y humedad.
- Devuelve los valores en variables globales utilizadas por el resto del sistema.

### sensor_bmp180.cpp / sensor_bmp180.h

- Inicializa el sensor BMP180.
- Realiza las lecturas de presión atmosférica.
- Devuelve el valor de presión actualizado.

### oled_display.cpp / oled_display.h (opcional)

- Inicializa la pantalla OLED.
- Visualiza las últimas lecturas de los sensores en pantalla.
- Utiliza la librería U8g2 para manejo gráfico.

### wifi.cpp / wifi.h

- Configura la conexión WiFi.
- Implementa lógica de reconexión automática en caso de pérdida de enlace.

### mqtt.cpp / mqtt.h

- Inicializa el cliente MQTT mediante la librería PubSubClient.
- Publica periódicamente los datos adquiridos hacia el broker MQTT configurado (Mosquitto).
- Mantiene la conexión activa mediante función de reconexión automática.

### serial_commands.cpp / serial_commands.h

- Interpreta comandos ingresados por puerto serie.
- Permite modificar dinámicamente los parámetros de configuración (umbral, intervalo de muestreo, etc.).
- Actualiza los valores persistentes en NVS tras cada modificación.

### storage.cpp / storage.h

- Implementa la lectura y escritura de parámetros en el sistema de persistencia no volátil (NVS).
- Garantiza la conservación de configuraciones incluso tras reinicios del sistema.

### config.h

- Define constantes generales de configuración.
- Centraliza pines, credenciales de red, parámetros iniciales y estructura del sistema.

## Flujo de funcionamiento detallado

1. Al iniciar, el sistema recupera desde NVS los parámetros previamente almacenados.
2. Establece la conexión WiFi con los parámetros definidos.
3. Inicializa los sensores conectados.
4. Se conecta al broker MQTT.
5. En el bucle principal:
   - Lee los sensores DHT22 y BMP180.
   - Publica los valores de temperatura, humedad y presión mediante MQTT.
   - Si corresponde, actualiza la visualización en la pantalla OLED.
   - Monitorea comandos por puerto serie para posibles ajustes de parámetros.
6. Si se produce una desconexión de red o broker MQTT, el sistema intenta reconectar automáticamente.

## Esquema de conexión

pendiente

## Instalación

1. Clonar el repositorio:

git clone https://github.com/lucasrosutn/estacionmeteorologica.git


2. Abrir el proyecto con PlatformIO en Visual Studio Code.
3. Instalar las librerías definidas en el archivo `platformio.ini`.
4. Configurar los parámetros iniciales en `config.h` (pines, credenciales WiFi, topic MQTT).
5. Realizar el cableado según el esquema de conexión.
6. Compilar y cargar el programa en el ESP32.
7. Verificar el funcionamiento mediante monitor serial y suscripción MQTT.

## Notas adicionales

- El broker MQTT utilizado es **Mosquitto**. El sistema puede conectarse a cualquier servidor MQTT compatible configurado previamente.
- No se implementa almacenamiento local de históricos. Las variables de configuración persistente se almacenan únicamente en NVS.
- El sistema admite modificaciones futuras incorporando nuevos sensores o ampliando las funcionalidades de comunicación.

## Licencia

Este proyecto se presenta exclusivamente con fines académicos, bajo las normas de la institución.

## Autor

Lucas Rosemberg - Año 2025
