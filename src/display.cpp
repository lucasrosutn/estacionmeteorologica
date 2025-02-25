#include "display.h"
#include <U8g2lib.h>
#include <Wire.h>

// Global instance of the display OLED SSH1106
//U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* SCL=*/ 22, /* SDA=*/ 21);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, SCL_PIN, SDA_PIN);
uint8_t u8log_buffer[U8LOG_WIDTH*U8LOG_HEIGHT];
U8X8LOG u8x8log;

void initDisplay() {
  Wire.begin(SDA_PIN,SCL_PIN);
  u8g2.begin();
  u8x8log.begin(U8LOG_WIDTH, U8LOG_HEIGHT, u8log_buffer);
  u8x8log.setRedrawMode(1);		//--  0: Update screen with newline, 1: Update screen for every char  
  //u8g2.setFlipMode(1);        //--  rotate screen 180 degrees
}

void oled88_bienvenida(void){
  u8g2.setMaxClipWindow();
  u8g2.setFont(u8g2_font_spleen6x12_mf);
  u8g2.setCursor(10,35);
  u8g2.print("UTN Electronica II");
  u8g2.setFont(u8g2_font_streamline_all_t); //see https://github.com/olikraus/u8g2/wiki/fntgrpstreamline#streamline_all
  u8g2.sendBuffer();
  delay(500);
}

void mostrarDatos(float temperatura, float humedad, float presion) {
    u8g2.clearBuffer();
    u8g2.sendBuffer();
    u8g2.setFont(u8g2_font_spleen6x12_mf);

    // Shows temperature
    u8g2.setCursor(3, 20);
    u8g2.print("Temp: ");
    u8g2.print(temperatura);
    u8g2.print(" C");

    // Shows humidity
    u8g2.setCursor(3, 40);
    u8g2.print("Hum: ");
    u8g2.print(humedad);
    u8g2.print(" %");

    // Shows atmospheric pressure
    u8g2.setCursor(3, 60);
    u8g2.print("Pres: ");
    u8g2.print(presion);
    u8g2.print(" hPa");

    u8g2.sendBuffer();
}
