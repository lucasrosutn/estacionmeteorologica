#include <Arduino.h>
#include "setup.h"
#include "app.h"

// Configuración inicial del programa
void setup() {
    setupSystem(); // Llama a la configuración del sistema
}

// Ciclo principal del programa
void loop() {
    runApp(); // Ejecuta la lógica principal de la aplicación
}
