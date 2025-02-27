#ifndef SERIAL_COMMANDS_H
#define SERIAL_COMMANDS_H

#include "Arduino.h"
#include "storage.h"

//Function in charge of checking serial port and refresh parameters in the storage if needed. Gets the instance "storage" 
//as a reference to work on it 
void checkSerialCommands(Storage &storage);

#endif
