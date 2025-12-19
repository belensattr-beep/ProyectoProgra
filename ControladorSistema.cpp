//controladorsistema.cpp
#include "ControladorSistema.h"

ControladorSistema::ControladorSistema(byte pinSelector)
  : nfc(21, 22), sd(5), buzzer(32), selector(pinSelector),
    // Inyectamos el hardware a los modos
    kiosko(lcd, buzzer, reloj, sd, nfc, teclado),
    cobro(lcd, nfc, sd, reloj, buzzer),
    modoActual(nullptr) {}

void ControladorSistema::iniciar() {
  // Centralizamos la inicialización física 
  lcd.iniciar();
  buzzer.iniciar();
  reloj.iniciar();
  sd.iniciar();
  nfc.iniciar();
}

void ControladorSistema::ejecutar() {
  // Leemos el selector físico
  bool esKiosko = selector.esKiosko();
  Modo* nuevoModo = esKiosko ? (Modo*)&kiosko : (Modo*)&cobro;

  // Si el switch cambió de posición
  if (modoActual != nuevoModo) {
    if (modoActual) {
      modoActual->alSalir();
    }
    nuevoModo->alEntrar();
    modoActual = nuevoModo;
  }

  // Ejecutamos la lógica del modo activo
  if (modoActual) {
    modoActual->ejecutar();
  }
}