//ino
#include <Arduino.h>
#include <Wire.h>
#include "ControladorSistema.h"

ControladorSistema& obtenerSistema() {
    static ControladorSistema instancia(27); // Pin del switch
    return instancia;
}
void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // Pines I2C para el LCD
  
  obtenerSistema().iniciar(); // Inicializa todo el hardware una sola vez
}

void loop() {
  obtenerSistema().ejecutar(); // Controla el switch y ejecuta el modo activo
}

