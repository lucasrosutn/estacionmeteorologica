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

### SETUP 











### relay
- **initRelay()**: Configura el pin del relé como salida con `pinMode(RELAY_PIN, OUTPUT);`. Inicializa el relé apagado con `digitalWrite(RELAY_PIN, LOW);`.
- **controlRelay(float temperature, float humidity)**: Enciende el relé (`digitalWrite(RELAY_PIN, HIGH);`) si la temperatura es mayor a 25°C o si la humedad es mayor al 60%. Apaga el relé (`digitalWrite(RELAY_PIN, LOW);`) si ambas condiciones son menores a esos umbrales.
- **showState()**:
Retorna `true` si el relé está encendido (es decir, si el pin está en alto), y `false` si está apagado (pin en bajo).

### oled
- **initDisplay()**:
   - Inicializa la comunicación I2C con `Wire.begin(SDA_PIN, SCL_PIN);`.
   - Configura y empieza el display con `u8g2.begin();`.
   - Inicializa el buffer de log con `u8x8log.begin(U8LOG_WIDTH, U8LOG_HEIGHT, u8log_buffer);`.
   - Configura el modo de actualización del log.
- **oled88_welcome()**: Muestra un mensaje de bienvenida en el display, con el texto "SmartVent". Establece el tipo de fuente y la posición del texto en la pantalla. Utiliza `u8g2.sendBuffer()` para enviar los datos a la pantalla después de dibujar.
- **showData(float temperature, float humidity)**:
   - Borra la pantalla actual con `u8g2.clearBuffer();`.
   - Muestra la temperatura, humedad y el estado del ventilador (relé) en posiciones específicas de la pantalla.
   - Muestra "ON" si el relé está encendido o "OFF" si está apagado, utilizando la función `showState()` del archivo `relay.h`.
   - Actualiza la pantalla con los datos mediante `u8g2.sendBuffer();`.

### wificonnection
- **wifi_init():** Inicializa la conexión Wi-Fi en el modo especificado (`WIFI_AP_STA`, `WIFI_AP`, `WIFI_STA`).
- **wifi_loop():** Mantiene la conexión Wi-Fi utilizando una máquina de estados: `CONNECTED`, `RECONNECT`, `DISCONNECTED`, `WAITTORECONNECT`, `WAITFORCONNECT`. Devuelve `true` si la conexión está activa, `false` si no.

### Storage
Este código permite almacenar y recuperar datos de configuración (SSID, contraseña y dirección del broker MQTT) en la memoria flash del ESP32, asegurando que la información persista entre reinicios.
- **getSSID():** Retorna el SSID guardado en memoria.
- **getPassword():** Retorna la contraseña guardada.
- **getBrokerIP():** Retorna la dirección IP del broker MQTT.

### Commands
- **checkSerialCommands:** Extrae el nuevo SSID, contraseña e IP del broker de la cadena y lo guarda en el objeto Storage.

### MQTT
- **setupMQTT():** Configura el cliente MQTT con el servidor y puerto definidos. Establece el callback para manejar los mensajes entrantes (`mqttCallback`).
- **reconnectMQTT():** Intenta conectar al broker MQTT en un bucle:
   - Si la conexión es exitosa, imprime un mensaje de éxito y se suscribe al tópico "smartvent/commands".
   - Si no se puede conectar, espera 5 segundos y lo intenta de nuevo.
- **mqttCallback(char* topic, byte* payload, unsigned int length):** Esta función es llamada cuando el cliente MQTT recibe un mensaje en un tópico. Convierte el tópico y el mensaje (payload) en cadenas de texto (`String`). Imprime los datos del tópico y el mensaje recibido en la consola para depuración.

### Publish
- **publishTemperature(float temperature)**: Convierte el valor de temperatura a un `String`. Publica el valor en el tópico MQTT "smartvent/temperature". Imprime en la consola si la publicación fue exitosa o no.
- **publishHumidity(float humidity)**: Convierte el valor de humedad a un `String`. Publica el valor en el tópico MQTT "smartvent/humidity". Imprime en la consola si la publicación fue exitosa o no.
- **publishRelayState(bool state)**: Convierte el estado del relé (true o false) a un string "ON" o "OFF". Publica el estado en el tópico MQTT "smartvent/relay". Imprime en la consola si la publicación fue exitosa o no.

### Setup
- **Configuración de la Comunicación Serie**: Inicia la comunicación serial a 19200 baudios.
- **initSensor()**: Inicializa el sensor DHT11 para medir temperatura y humedad.
- **initDisplay()**: Inicializa la pantalla OLED.
- **oled88_welcome()**: Muestra un mensaje de bienvenida en la pantalla.
- **initRelay()**: Inicializa el relé que controla el ventilador.
- **setupMQTT()**: Inicializa la conexión MQTT.
- **storage.begin()**: Inicia el acceso a la memoria persistente.
- **wifi_init(WIFI_AP_STA)**: Configura el ESP32 para operar en modo estación y punto de acceso simultáneamente.
- **connectMQTT()**: Conecta al broker MQTT.

### App
- **readTemperature()**: Lee la temperatura del sensor DHT11.
- **readHumidity()**: Lee la humedad del sensor DHT11.
- **showData(temperature, humidity)**: Muestra los valores de temperatura y humedad en la pantalla OLED.
- **controlRelay(temperature, humidity)**: Activa o desactiva el relé según las condiciones de temperatura y humedad. El relé se activa si la temperatura es mayor a 25°C o si la humedad es superior al 60%.
- **publishTemperature(temperature)**: Publica la temperatura medida en el broker MQTT.
- **publishHumidity(humidity)**: Publica la humedad medida en el broker MQTT.
- **publishRelayState(showState())**: Publica el estado del relé (encendido o apagado) en el broker MQTT.
- **wifi_state = wifi_loop()**: Llama a la función `wifi_loop()`, que gestiona la conexión Wi-Fi. Si la conexión se pierde, intenta reconectarse.
- **checkSerialCommands(storage)**: Verifica si hay comandos entrantes por el puerto serial.

### Main
- **setup()**: Se llama al principio cuando el sistema arranca. Ejecuta la función `setupSystem()` que configura el sistema, incluyendo la inicialización de componentes como el sensor DHT11, el display OLED, el relé, la conexión WiFi y la configuración MQTT.
- **loop()**: Se ejecuta de manera continua después de `setup()`. Llama a la función `runApp()`, que se encarga de manejar el ciclo principal del programa.

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