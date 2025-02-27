#ifndef DISPLAY_H
#define DISPLAY_H

//--Oled pin definitions
#define SCL_PIN         22
#define SDA_PIN         21
#define U8LOG_WIDTH     16
#define U8LOG_HEIGHT    8

//oled functions
void initDisplay(); //initializacion
void oled88_bienvenida(void); //welcome message
void mostrarDatos(float temperatura, float humedad, float presion); //shows data

#endif
