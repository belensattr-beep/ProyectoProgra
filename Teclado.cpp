//teclado.cpp
#include "Teclado.h"

Teclado::Teclado()
  : keypad(makeKeymap(teclas), pinesFilas, pinesCols, FILAS, COLS), buffer("") {}

bool Teclado::leerMontoNoBloqueante(float &monto, PantallaLCD &lcd){
  char k = keypad.getKey();
  if (!k) return false;
  if (k >= '0' && k <= '9') {
    buffer += k;
    lcd.mensaje("Monto:", buffer);
  }
  else if (k == '*') {
    buffer = "";
    lcd.mensaje("Monto:", buffer);
  }
  else if (k == '#') {
    if (buffer.length() > 0) {
      monto = buffer.toFloat();
      buffer = "";   // limpiar para la próxima
      return true;   // 👈 TERMINÓ
    }
  }
  return false;  // todavía no terminó
}

bool Teclado::leerTipoNoBloqueante(char& tipo, PantallaLCD& lcd) {
  char k = keypad.getKey();
  if (!k) return false;

  if (k == '1' || k == '2' || k == '3') {
    tipo = k;
    return true;   // 👈 tipo seleccionado
  }

  return false;    // todavía esperando
}