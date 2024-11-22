#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include <RTClib.h>
#include <Wire.h>

extern MCUFRIEND_kbv tft;
extern TouchScreen ts;

class Funciones {
private:
  MCUFRIEND_kbv &tft;
  TouchScreen &ts;

public:
  Funciones(MCUFRIEND_kbv &tft, TouchScreen &ts)
    : tft(tft), ts(ts) {}
  const int buttonSize = (480 - (10 * 5)) / 4;
  const int buttonMargin = 10;

  struct Button {
    int x, y, size;
    const char *label;
    uint16_t color;
  };

  void checkTouch();
  void drawMenu(uint16_t id);
  void drawInit();
  void executeButton(int buttonIndex);
};

#endif  // FUNCIONES_H
