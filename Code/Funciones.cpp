#include "Funciones.h"

// Parámetros del touch
#define TS_LEFT 900
#define TS_RT 220
#define TS_TOP 965
#define TS_BOT 165

// Pines de la pantalla táctil
#define XP 6   // Pin para el canal X+
#define YP A1  // Pin para el canal Y+
#define XM A2  // Pin para el canal X-
#define YM 7   // Pin para el canal Y-

// Colores para uso sencillo
#define COLOR_BLACK 0x0000    // Negro
#define COLOR_WHITE 0xFFFF    // Blanco
#define COLOR_RED 0xF800      // Rojo
#define COLOR_GREEN 0x07E0    // Verde
#define COLOR_BLUE 0x001F     // Azul
#define COLOR_CYAN 0x07FF     // Cian
#define COLOR_MAGENTA 0xF81F  // Magenta
#define COLOR_YELLOW 0xFFE0   // Amarillo
#define COLOR_ORANGE 0xFD20   // Naranja
#define COLOR_PURPLE 0x780F   // Púrpura
#define COLOR_GRAY 0x8410     // Gris
#define COLOR_BROWN 0xA145    // Marrón

RTC_DS1307 rtc;
MCUFRIEND_kbv tft;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
uint16_t id = 0;

enum Menu {
  MENU_PRINCIPAL,
  MENU_MACROS_1,
  MENU_MACROS_2,
  MENU_DISCORD,
  MENU_AUDIO,
  MENU_SOUNDPAD,
  MENU_CONFIG
};

Menu menuActual = MENU_PRINCIPAL;

void Funciones::drawInit()
{
  tft.fillScreen(COLOR_BLACK);
  tft.setTextColor(COLOR_WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 10);

  tft.print("Pantalla TFT inicializada correctamente");
  tft.setCursor(10, 30);

  Wire.begin();
  if (!rtc.begin())
  {
    tft.print("No se pudo encontrar el RTC");
    tft.setCursor(10, 50);
    tft.setTextColor(COLOR_RED);
    tft.print("Program terminated");
    while (1);
  }

  if (!rtc.isrunning())
  {
    tft.print("RTC no está en funcionamiento, ajustando la hora...");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  else
  {
    tft.print("RTC configurada correctamente");
  }
  
  tft.setCursor(10, 50);
  tft.print("Esperando mensaje del ESP32...");
  while (!Serial1.available())
  {
    delay(10);
  }

  String message = Serial1.readStringUntil('\n');
  tft.setCursor(10, 70);

  if (message == "ESP32 READY")
  {
    tft.setTextColor(COLOR_GREEN);
    tft.print("ESP32 conectado");
    Serial1.println("OK");
  }
  else
  {
    tft.setTextColor(COLOR_RED);
    tft.print("No se recibió mensaje del ESP32");
    tft.setCursor(10, 90);
    tft.print("Program terminated");
    while (1);
  }
  
  // Aquí podrías añadir otras comprobaciones de módulos adicionales
  // Ejemplo: Comprobación de tarjeta SD o sensores adicionales
  // if (!sd.begin()) {
  //   tft.setCursor(10, 70);
  //   tft.print("Error al inicializar la tarjeta SD");
  //   while (1);
  // }
  tft.setCursor(10, 90);
  tft.print("Inicializacion completada.");
  id = tft.readID();
  delay(2000);
  drawMenu(id);
}

void Funciones::drawMenu(uint16_t id)
{
  tft.fillScreen(COLOR_BLACK);

  Button MenuP[8] = {
    { buttonMargin, buttonMargin, buttonSize, "Macros 1", COLOR_WHITE },
    { buttonMargin * 2 + buttonSize, buttonMargin, buttonSize, "Macros 2", COLOR_WHITE },
    { buttonMargin * 3 + buttonSize * 2, buttonMargin, buttonSize, "Discord", COLOR_WHITE },
    { buttonMargin * 4 + buttonSize * 3, buttonMargin, buttonSize, "Audio", COLOR_WHITE },
    { buttonMargin, buttonMargin * 2 + buttonSize, buttonSize, "SoundPad", COLOR_WHITE },
    { buttonMargin * 2 + buttonSize, buttonMargin * 2 + buttonSize, buttonSize, "N/A", COLOR_WHITE },
    { buttonMargin * 3 + buttonSize * 2, buttonMargin * 2 + buttonSize, buttonSize, "N/A", COLOR_WHITE },
    { buttonMargin * 4 + buttonSize * 3, buttonMargin * 2 + buttonSize, buttonSize, "Config", COLOR_WHITE }
  };

  Button MenuM1[8] = {
    { buttonMargin, buttonMargin, buttonSize, "Atras", COLOR_WHITE },
    { buttonMargin * 2 + buttonSize, buttonMargin, buttonSize, "Firefox", COLOR_WHITE },
    { buttonMargin * 3 + buttonSize * 2, buttonMargin, buttonSize, "Discord", COLOR_WHITE },
    { buttonMargin * 4 + buttonSize * 3, buttonMargin, buttonSize, "Steam", COLOR_WHITE },
    { buttonMargin, buttonMargin * 2 + buttonSize, buttonSize, "Soundpad", COLOR_WHITE },
    { buttonMargin * 2 + buttonSize, buttonMargin * 2 + buttonSize, buttonSize, "Spotify", COLOR_WHITE },
    { buttonMargin * 3 + buttonSize * 2, buttonMargin * 2 + buttonSize, buttonSize, "etc", COLOR_WHITE },
    { buttonMargin * 4 + buttonSize * 3, buttonMargin * 2 + buttonSize, buttonSize, "etc", COLOR_WHITE }
  };

  Button MenuM2[8] = {
    { buttonMargin, buttonMargin, buttonSize, "Atras", COLOR_WHITE },
    { buttonMargin * 2 + buttonSize, buttonMargin, buttonSize, "etc", COLOR_WHITE },
    { buttonMargin * 3 + buttonSize * 2, buttonMargin, buttonSize, "etc", COLOR_WHITE },
    { buttonMargin * 4 + buttonSize * 3, buttonMargin, buttonSize, "etc", COLOR_WHITE },
    { buttonMargin, buttonMargin * 2 + buttonSize, buttonSize, "etc", COLOR_WHITE },
    { buttonMargin * 2 + buttonSize, buttonMargin * 2 + buttonSize, buttonSize, "etc", COLOR_WHITE },
    { buttonMargin * 3 + buttonSize * 2, buttonMargin * 2 + buttonSize, buttonSize, "etc", COLOR_WHITE },
    { buttonMargin * 4 + buttonSize * 3, buttonMargin * 2 + buttonSize, buttonSize, "etc", COLOR_WHITE }
  };

  Button MenuD[8] = {
    { buttonMargin, buttonMargin, buttonSize, "Atras", COLOR_WHITE },
    { buttonMargin * 2 + buttonSize, buttonMargin, buttonSize, "Un/Mute", COLOR_WHITE },
    { buttonMargin * 3 + buttonSize * 2, buttonMargin, buttonSize, "Un/Deaf", COLOR_WHITE },
    { buttonMargin * 4 + buttonSize * 3, buttonMargin, buttonSize, "Un/Stream", COLOR_WHITE },
    { buttonMargin, buttonMargin * 2 + buttonSize, buttonSize, "Un/Cam", COLOR_WHITE },
    { buttonMargin * 2 + buttonSize, buttonMargin * 2 + buttonSize, buttonSize, "Stream Mode", COLOR_WHITE },
    { buttonMargin * 3 + buttonSize * 2, buttonMargin * 2 + buttonSize, buttonSize, "N/A", COLOR_WHITE },
    { buttonMargin * 4 + buttonSize * 3, buttonMargin * 2 + buttonSize, buttonSize, "N/A", COLOR_WHITE }
  };

  Button MenuA[8] = {
    { buttonMargin, buttonMargin, buttonSize, "Atras", COLOR_WHITE },
    { buttonMargin * 2 + buttonSize, buttonMargin, buttonSize, "N/A", COLOR_WHITE },
    { buttonMargin * 3 + buttonSize * 2, buttonMargin, buttonSize, "N/A", COLOR_WHITE },
    { buttonMargin * 4 + buttonSize * 3, buttonMargin, buttonSize, "+ Vol", COLOR_WHITE },
    { buttonMargin, buttonMargin * 2 + buttonSize, buttonSize, "Back", COLOR_WHITE },
    { buttonMargin * 2 + buttonSize, buttonMargin * 2 + buttonSize, buttonSize, "Un/Pause", COLOR_WHITE },
    { buttonMargin * 3 + buttonSize * 2, buttonMargin * 2 + buttonSize, buttonSize, "Next", COLOR_WHITE },
    { buttonMargin * 4 + buttonSize * 3, buttonMargin * 2 + buttonSize, buttonSize, "- Vol", COLOR_WHITE }
  };

  Button MenuS[8] = {
    { buttonMargin, buttonMargin, buttonSize, "Atras", COLOR_WHITE },
    { buttonMargin * 2 + buttonSize, buttonMargin, buttonSize, "N/A", COLOR_WHITE },
    { buttonMargin * 3 + buttonSize * 2, buttonMargin, buttonSize, "N/A", COLOR_WHITE },
    { buttonMargin * 4 + buttonSize * 3, buttonMargin, buttonSize, "N/A", COLOR_WHITE },
    { buttonMargin, buttonMargin * 2 + buttonSize, buttonSize, "N/A", COLOR_WHITE },
    { buttonMargin * 2 + buttonSize, buttonMargin * 2 + buttonSize, buttonSize, "N/A", COLOR_WHITE },
    { buttonMargin * 3 + buttonSize * 2, buttonMargin * 2 + buttonSize, buttonSize, "N/A", COLOR_WHITE },
    { buttonMargin * 4 + buttonSize * 3, buttonMargin * 2 + buttonSize, buttonSize, "N/A", COLOR_WHITE }
  };

  Button MenuC[8] = {
    { buttonMargin, buttonMargin, buttonSize, "Atras", COLOR_WHITE },
    { buttonMargin * 2 + buttonSize, buttonMargin, buttonSize, "N/A", COLOR_WHITE },
    { buttonMargin * 3 + buttonSize * 2, buttonMargin, buttonSize, "N/A", COLOR_WHITE },
    { buttonMargin * 4 + buttonSize * 3, buttonMargin, buttonSize, "N/A", COLOR_WHITE },
    { buttonMargin, buttonMargin * 2 + buttonSize, buttonSize, "N/A", COLOR_WHITE },
    { buttonMargin * 2 + buttonSize, buttonMargin * 2 + buttonSize, buttonSize, "N/A", COLOR_WHITE },
    { buttonMargin * 3 + buttonSize * 2, buttonMargin * 2 + buttonSize, buttonSize, "N/A", COLOR_WHITE },
    { buttonMargin * 4 + buttonSize * 3, buttonMargin * 2 + buttonSize, buttonSize, "N/A", COLOR_WHITE }
  };

  Button btn;

  for (int i = 0; i < 8; ++i) {
    if (menuActual == MENU_PRINCIPAL)
    {
      btn = MenuP[i];
    }
    else if (menuActual == MENU_MACROS_1)
    {
      btn = MenuM1[i];
    }
    else if (menuActual == MENU_MACROS_2)
    {
      btn = MenuM2[i];
    }
    else if(menuActual == MENU_DISCORD)
    {
      btn = MenuD[i];
    }
    else if(menuActual == MENU_AUDIO)
    {
      btn = MenuA[i];
    }
    else if(menuActual == MENU_SOUNDPAD)
    {
      btn = MenuS[i];
    }
    else
    {
      btn = MenuC[i];
    }
    
    tft.fillRect(btn.x, btn.y, btn.size, btn.size, btn.color);
    tft.drawRect(btn.x, btn.y, btn.size, btn.size, COLOR_BLACK);
    int textWidth = 6 * strlen(btn.label);
    int textX;
    if(i == 0 or i == 1)
    {
      textX = btn.x + (btn.size - textWidth) / 2 - 22;
    }
    else if(i == 2)
    {
      textX = btn.x + (btn.size - textWidth) / 2 - 20;
    }
    else if(i == 3 or i == 7)
    {
      textX = btn.x + (btn.size - textWidth) / 2 - 15;
    }
    else if(i == 4)
    {
      textX = btn.x + (btn.size - textWidth) / 2 - 23;
    }
    else
    {
      textX = btn.x + (btn.size - textWidth) / 2 - 9;
    }

    int textY = btn.y + (btn.size - 12) / 2 + 35;
    tft.setCursor(textX, textY);
    tft.setTextColor(COLOR_BLACK);
    tft.setTextSize(2);
    tft.print(btn.label);
  }
  int y = 250;
  for(int i = 0; i < 320; ++i)
  {
    tft.drawFastHLine(0, y, 480, COLOR_WHITE);
    ++y;
  }
}

void Funciones::executeButton(int buttonIndex)
{
  Serial.print("Botón ");
  Serial.print(buttonIndex + 1);  // Imprime el número del botón (1 a 8)
  Serial.println(" presionado");
}

void Funciones::checkTouch() {
  TSPoint p = ts.getPoint();

  // Ajustar el umbral de presión
  int pressureThreshold = 350;

  // Verifica si el toque es suficiente
  if (p.z > pressureThreshold) {
    // Ajustar mapeo para la rotación
    int x = map(p.x, TS_LEFT, TS_RT, 0, tft.width());
    int y = map(p.y, TS_TOP, TS_BOT, 0, tft.height());

    // Intercambiar x e y para la rotación de 90 grados a la derecha
    int temp = x;
    x = y;
    y = tft.height() - temp;

    // Verificar en qué botón se ha pulsado
    switch (menuActual) {
      case MENU_PRINCIPAL:
        // Botón 1
        if (x >= 10 && x <= 80 && y >= -150 && y <= 10) {
          menuActual = MENU_MACROS_1;
          drawMenu(id);
        }
        // Botón 2
        if (x >= 85 && x <= 155 && y >= -150 && y <= 10) {
          menuActual = MENU_MACROS_2;
          drawMenu(id);
        }
        // Botón 3
        if (x >= 160 && x <= 230 && y >= -150 && y <= 10) {
          menuActual = MENU_DISCORD;
          drawMenu(id);
        }
        // Botón 4
        if (x >= 235 && x <= 295 && y >= -150 && y <= 10) {
          menuActual = MENU_AUDIO;
          drawMenu(id);
        }
        // Botón 5
        if (x >= 10 && x <= 80 && y >= 25 && y <= 200) {
          menuActual = MENU_SOUNDPAD;
          drawMenu(id);
        }
        // Botón 6
        if (x >= 85 && x <= 155 && y >= 25 && y <= 200) {
          executeButton(5);
        }
        // Botón 7
        if (x >= 160 && x <= 230 && y >= 25 && y <= 200) {
          executeButton(6);
        }
        // Botón 8
        if (x >= 235 && x <= 295 && y >= 25 && y <= 200) {
          menuActual = MENU_CONFIG;
          drawMenu(id);
        }

        delay(200);  // Pequeña pausa para evitar múltiples detecciones
        break;
      case MENU_MACROS_1:
        // Botón 1
        if (x >= 10 && x <= 80 && y >= -150 && y <= 10) {
          menuActual = MENU_PRINCIPAL;
          drawMenu(id);
        }
        // Botón 2
        if (x >= 85 && x <= 155 && y >= -150 && y <= 10) {
          Serial.print("B: 1, M: Macro1\n");
        }
        // Botón 3
        if (x >= 160 && x <= 230 && y >= -150 && y <= 10) {
          Serial.print("B: 2, M: Macro1\n");
        }
        // Botón 4
        if (x >= 235 && x <= 295 && y >= -150 && y <= 10) {
          Serial.print("B: 3, M: Macro1\n");
        }
        // Botón 5
        if (x >= 10 && x <= 80 && y >= 25 && y <= 200) {
          Serial.print("B: 4, M: Macro1\n");
        }
        // Botón 6
        if (x >= 85 && x <= 155 && y >= 25 && y <= 200) {
          executeButton(5);
        }
        // Botón 7
        if (x >= 160 && x <= 230 && y >= 25 && y <= 200) {
          executeButton(6);
        }
        // Botón 8
        if (x >= 235 && x <= 295 && y >= 25 && y <= 200) {
          executeButton(7);
        }

        delay(200);
        break;
      case MENU_MACROS_2:
        // Botón 1
        if (x >= 10 && x <= 80 && y >= -150 && y <= 10) {
          menuActual = MENU_PRINCIPAL;
          drawMenu(id);
        }
        // Botón 2
        if (x >= 85 && x <= 155 && y >= -150 && y <= 10) {
          executeButton(1);
        }
        // Botón 3
        if (x >= 160 && x <= 230 && y >= -150 && y <= 10) {
          executeButton(2);
        }
        // Botón 4
        if (x >= 235 && x <= 295 && y >= -150 && y <= 10) {
          executeButton(3);
        }
        // Botón 5
        if (x >= 10 && x <= 80 && y >= 25 && y <= 200) {
          executeButton(4);
        }
        // Botón 6
        if (x >= 85 && x <= 155 && y >= 25 && y <= 200) {
          executeButton(5);
        }
        // Botón 7
        if (x >= 160 && x <= 230 && y >= 25 && y <= 200) {
          executeButton(6);
        }
        // Botón 8
        if (x >= 235 && x <= 295 && y >= 25 && y <= 200) {
          executeButton(7);
        }
        delay(200);
        break;
      case MENU_DISCORD:
        // Botón 1
        if (x >= 10 && x <= 80 && y >= -150 && y <= 10) {
          menuActual = MENU_PRINCIPAL;
          drawMenu(id);
        }
        // Botón 2
        if (x >= 85 && x <= 155 && y >= -150 && y <= 10) {
          executeButton(1);
        }
        // Botón 3
        if (x >= 160 && x <= 230 && y >= -150 && y <= 10) {
          executeButton(2);
        }
        // Botón 4
        if (x >= 235 && x <= 295 && y >= -150 && y <= 10) {
          executeButton(3);
        }
        // Botón 5
        if (x >= 10 && x <= 80 && y >= 25 && y <= 200) {
          executeButton(4);
        }
        // Botón 6
        if (x >= 85 && x <= 155 && y >= 25 && y <= 200) {
          executeButton(5);
        }
        // Botón 7
        if (x >= 160 && x <= 230 && y >= 25 && y <= 200) {
          executeButton(6);
        }
        // Botón 8
        if (x >= 235 && x <= 295 && y >= 25 && y <= 200) {
          executeButton(7);
        }

        delay(200);
      break;

      case MENU_AUDIO:
        // Botón 1
        if (x >= 10 && x <= 80 && y >= -150 && y <= 10) {
          menuActual = MENU_PRINCIPAL;
          drawMenu(id);
        }
        // Botón 2
        if (x >= 85 && x <= 155 && y >= -150 && y <= 10) {
          executeButton(1);
        }
        // Botón 3
        if (x >= 160 && x <= 230 && y >= -150 && y <= 10) {
          executeButton(2);
        }
        // Botón 4
        if (x >= 235 && x <= 295 && y >= -150 && y <= 10) {
          executeButton(3);
        }
        // Botón 5
        if (x >= 10 && x <= 80 && y >= 25 && y <= 200) {
          executeButton(4);
        }
        // Botón 6
        if (x >= 85 && x <= 155 && y >= 25 && y <= 200) {
          executeButton(5);
        }
        // Botón 7
        if (x >= 160 && x <= 230 && y >= 25 && y <= 200) {
          executeButton(6);
        }
        // Botón 8
        if (x >= 235 && x <= 295 && y >= 25 && y <= 200) {
          executeButton(7);
        }
        delay(200);
      break;

      case MENU_SOUNDPAD:
        // Botón 1
        if (x >= 10 && x <= 80 && y >= -150 && y <= 10) {
          menuActual = MENU_PRINCIPAL;
          drawMenu(id);
        }
        // Botón 2
        if (x >= 85 && x <= 155 && y >= -150 && y <= 10) {
          executeButton(1);
        }
        // Botón 3
        if (x >= 160 && x <= 230 && y >= -150 && y <= 10) {
          executeButton(2);
        }
        // Botón 4
        if (x >= 235 && x <= 295 && y >= -150 && y <= 10) {
          executeButton(3);
        }
        // Botón 5
        if (x >= 10 && x <= 80 && y >= 25 && y <= 200) {
          executeButton(4);
        }
        // Botón 6
        if (x >= 85 && x <= 155 && y >= 25 && y <= 200) {
          executeButton(5);
        }
        // Botón 7
        if (x >= 160 && x <= 230 && y >= 25 && y <= 200) {
          executeButton(6);
        }
        // Botón 8
        if (x >= 235 && x <= 295 && y >= 25 && y <= 200) {
          executeButton(7);
        }
        delay(200);
      break;

      case MENU_CONFIG:
        // Botón 1
        if (x >= 10 && x <= 80 && y >= -150 && y <= 10) {
          menuActual = MENU_PRINCIPAL;
          drawMenu(id);
        }
        // Botón 2
        if (x >= 85 && x <= 155 && y >= -150 && y <= 10) {
          executeButton(1);
        }
        // Botón 3
        if (x >= 160 && x <= 230 && y >= -150 && y <= 10) {
          executeButton(2);
        }
        // Botón 4
        if (x >= 235 && x <= 295 && y >= -150 && y <= 10) {
          executeButton(3);
        }
        // Botón 5
        if (x >= 10 && x <= 80 && y >= 25 && y <= 200) {
          executeButton(4);
        }
        // Botón 6
        if (x >= 85 && x <= 155 && y >= 25 && y <= 200) {
          executeButton(5);
        }
        // Botón 7
        if (x >= 160 && x <= 230 && y >= 25 && y <= 200) {
          executeButton(6);
        }
        // Botón 8
        if (x >= 235 && x <= 295 && y >= 25 && y <= 200) {
          executeButton(7);
        }
        delay(200);
      break;
    }
  }
}
