#include <MCUFRIEND_kbv.h>    
#include "Funciones.h"

// Pines de la pantalla TFT y táctil
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

// Crea el objeto para la pantalla y touch
Funciones funciones(tft, ts);

void drawMenu();
void checkTouch();

void setup()
{
  Serial.begin(9600);
  Serial1.begin(115200);
  tft.reset();
  uint16_t id = tft.readID();
  tft.begin(id);
  tft.setRotation(1);
  funciones.drawInit();
}

void loop()
{
  funciones.checkTouch();
}
