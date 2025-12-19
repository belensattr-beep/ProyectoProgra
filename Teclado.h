//teclado.h
#ifndef TECLADO_H
#define TECLADO_H

#include <Keypad.h>
#include "SistemaTransporte.h"

class Teclado {
private:
  static const byte FILAS = 4;
  static const byte COLS  = 4;
  String buffer;

  char teclas[FILAS][COLS] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
  };

  byte pinesFilas[FILAS] = {4, 12, 13, 14};
  byte pinesCols[COLS]  = {16, 17, 25, 26};

  Keypad keypad;

public:
  Teclado();

  bool leerMontoNoBloqueante(float& monto, PantallaLCD& lcd);
  bool leerTipoNoBloqueante(char& tipo, PantallaLCD& lcd);

};

#endif
