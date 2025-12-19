//controladorsistema.h
#ifndef CONTROLADOR_SISTEMA_H
#define CONTROLADOR_SISTEMA_H

#include "ModoKiosko.h"
#include "ModoCobro.h"
#include "SelectorModo.h"
#include "SistemaTransporte.h"
#include "Teclado.h"

class ControladorSistema {
private:
  // Instancias únicas de Hardware
  PantallaLCD lcd;
  Buzzer     buzzer;
  Reloj      reloj;
  AlmacenSD  sd;
  LectorNFC  nfc;
  Teclado    teclado;

  SelectorModo selector;
  
  // Modos que reciben referencias al hardware
  ModoKiosko kiosko;
  ModoCobro  cobro;
  Modo* modoActual;

public:
  ControladorSistema(byte pinSelector);
  void iniciar();   // Se llama desde el setup() del .ino [cite: 2]
  void ejecutar();  // Se llama desde el loop() del .ino [cite: 3]
};

#endif