#include <Arduino.h>
#include "setup.h"
#include "app.h"
#include "wifi_.h"


// Initial configuration of the programm
void setup() {
    setupSystem(); // Calls the system configuration
}

// Main programm loop
void loop() {
    runApp(); // Executes the main logic of the app
}
