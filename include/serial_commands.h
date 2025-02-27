#ifndef SERIAL_COMMANDS_H
#define SERIAL_COMMANDS_H

#include "Arduino.h"
#include "storage.h"

// Función que revisa el puerto serie y actualiza los parámetros en el Storage
// Recibe la instancia de Storage como referencia para trabajar sobre ella.
void checkSerialCommands(Storage &storage);

#endif
