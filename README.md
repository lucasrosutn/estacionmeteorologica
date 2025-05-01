# ESTACIÓN METEOROLÓGICA

El siguiente readme tiene por finalidad explicar el funcionamiento del código que rige la estación meteorológica.
El dispositivo mide temperatura, humedad relativa, presión y altitud.
Cuenta con la posiblidad de enviar los datos a un broker mediante el protoclo MQTT para ser consultado a distancia de su emplazamiento.

## Componentes
- **Microcontrolador:** ESP32
- **Sensor de temperatura y humedad relativa:** DHT22
- **Sensor de presión atmosférica y altitud:** BMP180
- **Actuador:** Led onboard azul asignado al pin 4 del microcontrolador
- **Visualización:** Display OLED
- **Conectividad:** Conexión wifi y comunicación MQTT con broker Mosquitto
- **Interfaz gráfica:** Dashboard en Node-RED

## Esquemáticos:
![Diagrama del circuito](images/Circuit.png)
![Diagrama del circuito](images/Schematic.png)

### Conexiones:
![Conexiones](images/Connections.png)

## Funcionamiento
El ESP32 procesa los datos recogidos mediante los sensores y los promedia para disminuir el error en estado estable. 
Los datos son mostrados en el display OLED y enviados al broker para su visualización remota en Node-Red.
A nivel local, el led onboard parpadea, generando asi una alarma local de tipo visual, cuando los valores de humedad relativa y temperatura configurados como valores límites son superados. Estos valores pueden ser modificados mediante comandos en el puerto serie así como el resto de las variables necesarias en caso de modificar el emplazamiento de la estación. Estos son: SSID, contraseña de la red, IP del broker (en caso de utilizar uno diferente)

## Instrucciones para el usuario
### Comandos a ingresar a través del puerto serie

//Escribiendo T=28.5 se actualizará el umbral de temperatura a 28.5°C.
//Escribiendo H=65.0 se actualizará el umbral de humedad a 65%.
//Escribiendo S=MiRedWiFi se actualizará el SSID.
//Escribiendo P=MiContraseña se actualizará la contraseña.
//Escribiendo B=192.168.1.50 se actualizará la IP del broker.
//Escribiendo SHOW se mostrarán los valores actuales.

## Funcionamiento del código
### SETUP
El archivo setup se ejecuta por única vez al encender el dispositivo y es el encargado de la configuración inicial.
```cpp
// Configurates the system initializing the necesary modules 
void setupSystem() {
    Serial.begin(19200);    // Initializes serial communication for debugging
    initSensor();           // Initilizes DHT22 sensor
    initDisplay();          // Initializes OLED display
    oled88_bienvenida();
    initBMP180();           // Initializes BMP180 sensor
    pinMode(LED_PIN,OUTPUT);
    welcome();
    setupMQTT();            // Initializes mqtt 
 
    pinMode(LED_PIN, OUTPUT);

    storage.begin();
    float tempThreshold = storage.getTempThreshold();
    float humThreshold  = storage.getHumThreshold();
    config.ssid         = storage.getSSID();
    config.ssid_pass     = storage.getPassword();
    config.broker_ip    = storage.getBrokerIP();
    
    
    // Prints the config to verify if it has been loaded succesfully
    Serial.println("Configuración cargada desde NVS:");
    Serial.print("Temp Threshold: "); Serial.println(tempThreshold);
    Serial.print("Hum Threshold: "); Serial.println(humThreshold);
    Serial.print("SSID: "); Serial.println(config.ssid);
    Serial.print("Password: "); Serial.println(config.ssid_pass);
    Serial.print("Broker IP: "); Serial.println(config.broker_ip);
  

    //--Init wifi

    wifi_init(WIFI_AP_STA);
    reconnectMQTT();
    timetopublish=millis();
}
```

### Main
Es el archivo principal. Se encarga de correr el setup y luego el archivo app donde se encuentra la lógica principal de la aplicación.
```cpp
// Initial configuration of the programm
void setup() {
    setupSystem(); // Calls the system configuration
}

// Main programm loop
void loop() {
    runApp(); // Executes the main logic of the app
}
```
### App
Es el archivo que contiene la lógica principal de la aplicación. 
Lo que aquí se realiza es el llamado a distintas funciones cuyo código se encuentra escrito en otros archivos para facilitar el mantenimiento y garantizar el orden de la aplicación.
Por ejemplo, en App.cpp se llama a los datos de humedad y temperatura obtenidos por el DHT22 pero que ya han sido procesados (promediados) en el archivo sensor_dht22.cpp

Ejemplo:
en app.cpp
```cpp
    // refreshes the readings of the sensor to update and refresh the buffer
    updateDHT22();
    //gets the promediated values of temoerature and humidity
    temperature = getAverageTemperature();
    humidity = getAverageHumidity();
    ```
    

    














## Requerimientos
- Hardware con las conexiones descriptas.
- Visual Studio Code instalado.
- PlatformIO instalado en Visual Studio Code.
- Mosquitto broker funcionando en la red local.
- Node-Red instalado con el dashboard activado.

## Configuración
1. **Clonar el repositorio:**
   ```sh
   git clone https://github.com/victoriafaiola/Sistema-de-Ventilacion.git
   ```
2. **Compilar y subir el firmware al ESP32:**
3. **Configurar Node-RED:**
   - Verificar la conexion wifi.
   - Verificarr la conexion con el broker Mosquitto.
   - Importar el archivo json en Node-Red.
   - Acceder a la dashboard.

## Dashboard en Node-RED
La interfaz permite:
- Visualizar temperatura y humedad en tiempo real.
- Visualizar la evolución de temperatura y humedad.
- Visualizar el estado del ventilador.