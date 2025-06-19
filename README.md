# Estación Meteorológica con ESP32

## Descripción

Este proyecto consiste en el desarrollo de una estación meteorológica basada en un microcontrolador **ESP32**. Permite la medición de temperatura, humedad y presión atmosférica, mostrando los datos en tiempo real y permitiendo su registro o visualización remota. El desarrollo se realizó como trabajo práctico para la asignatura universitaria correspondiente, aplicando programación modular y buenas prácticas de desarrollo embebido.

## Objetivos

- Aplicar conocimientos de sensores, comunicación y sistemas embebidos.
- Desarrollar código modular y escalable.
- Implementar adquisición de datos ambientales en tiempo real.
- Visualizar los datos localmente (pantalla OLED) o vía web.
- Documentar el proyecto de forma profesional, orientado a programadores.

## Materiales utilizados

### Hardware

- Placa **ESP32 DevKit**
- Sensor **DHT22** (temperatura y humedad)
- Sensor **BMP180** (presión)
- Display **OLED 0.96" I2C** (opcional)
- Protoboard y cables de conexión

### Software

- Plataforma: **PlatformIO (Visual Studio Code)** o **Arduino IDE**
- Lenguaje: **C++**
- Librerías utilizadas:
  - `Adafruit DHT Sensor Library`
  - `Adafruit Unified Sensor`
  - `Adafruit BMP180 Library`
  - `Adafruit SSD1306` (para el OLED)
  - `WiFi`

## 🔎 Descripción del código

El código está organizado en módulos independientes para facilitar su comprensión, mantenimiento y ampliación:

- **main.cpp**  
  Inicializa sensores, display, Wi-Fi, y ejecuta el ciclo principal de lectura de datos.

- **sensor_dht22.cpp / sensor_dht22.h**  
  Gestiona la lectura de temperatura y humedad desde el sensor DHT22.

- **sensor_bmp180.cpp / sensor_bmp180.h**  
  Gestiona la lectura de presión atmosférica desde el sensor BMP180.

- **oled_display.cpp / oled_display.h** *(opcional)*  
  Muestra los datos en tiempo real en la pantalla OLED.

- **wifi.cpp / wifi.h** *(opcional)*  
  Maneja la conexión Wi-Fi y el servidor web de visualización.

- **config.h**  
  Centraliza parámetros de configuración: pines, credenciales, intervalos de muestreo, etc.

### Flujo general de funcionamiento

1. El ESP32 inicia el sistema.
2. Inicializa los sensores.
3. Establece la conexión Wi-Fi (si corresponde).
4. Ejecuta el bucle principal donde:
   - Se leen los sensores.
   - Se actualizan variables.
   - Se actualiza el display OLED y/o se actualizan los datos en el servidor web.

### Consideraciones para programadores

- El código es modular y permite agregar fácilmente nuevos sensores.
- Los parámetros de configuración están centralizados en `config.h`.
- Las interfaces de sensores son independientes entre sí.
- El código es portable a otros microcontroladores compatibles.

## 📊 Esquema de conexión

Se presenta a continuación el diagrama de conexión de los componentes:

![Esquema de conexión](assets/esquema.png)

> *Nota: El esquema debe generarse con herramientas como Fritzing, EasyEDA o similar, y ubicarse en la carpeta `assets/`.*

## 🚀 Instalación

1. Clonar el repositorio:

```bash
git clone https://github.com/lucasrosutn/estacionmeteorologica.git
