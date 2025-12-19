//modocobro.cpp
#include "ModoCobro.h"

// Constructor que usa la lista de inicialización para las referencias de hardware
ModoCobro::ModoCobro(PantallaLCD& l, LectorNFC& n, AlmacenSD& s, Reloj& r, Buzzer& b)
  : lcd(l), nfc(n), sd(s), reloj(r), buzzer(b), estado(ESPERANDO_TARJETA), tMensaje(0) {}

void ModoCobro::iniciar() {
  // Vacío: El hardware ya fue iniciado por el ControladorSistema
}

float ModoCobro::tarifaPara(const Tarjeta* t) const {
  if (t->tipo() == "ESTUDIANTE")   return 1.00;
  if (t->tipo() == "ADULTO_MAYOR") return 1.50;
  return 2.30;
}

void ModoCobro::alEntrar() {
  estado = ESPERANDO_TARJETA;
  lcd.mensaje("MODO COBRO", "Acerque tarjeta");
  nfc.reset();
}

void ModoCobro::alSalir() {
  nfc.reset();
}

void ModoCobro::ejecutar() {
  // --- GESTIÓN DE TIEMPO DE MENSAJES (No bloqueante) ---
  if (estado == MOSTRANDO_OK || estado == MOSTRANDO_ERROR) {
    if (millis() - tMensaje >= 2500) { // Pausa para que el usuario lea la pantalla
      alEntrar(); // Reinicia al estado de espera
    }
    return;
  }

  // --- LÓGICA DE COBRO ---
  if (estado == ESPERANDO_TARJETA) {
    String uid;
    // Si no hay tarjeta presente, salimos para no bloquear el loop
    if (!nfc.leerUID(uid)) {
      return;
    }

    Tarjeta* t = sd.cargarTarjeta(uid);

    // 1. Verificación: ¿Existe la tarjeta?
    if (!t) {
      buzzer.error();
      lcd.mensaje("ERROR", "No registrada");
      estado = MOSTRANDO_ERROR;
      tMensaje = millis();
      return;
    }

    // 2. Verificación: ¿Tiene saldo suficiente?
    float tarifa = tarifaPara(t);
    if (!t->cobrar(tarifa)) {
      buzzer.error();
      lcd.mensaje("SALDO INSUF.", "Saldo: " + String(t->getSaldo(), 2));
      delete t; // ¡Importante! Liberar memoria
      estado = MOSTRANDO_ERROR;
      tMensaje = millis();
      return;
    }

    // 3. Proceso de Cobro Exitoso
    sd.guardarTarjeta(t); // Actualiza la base de datos en la SD
    
    // Registro de operación
    String f, h;
    reloj.ahora(f, h);
    sd.guardarOperacion(f + "," + h + "," + uid + "," + t->tipo() + ",PASAJE," + String(tarifa, 2) + "," + String(t->getSaldo(), 2));

    buzzer.ok();
    lcd.mensaje("PASAJE OK", "Saldo: " + String(t->getSaldo(), 2));
    
    delete t; // Liberar memoria
    estado = MOSTRANDO_OK;
    tMensaje = millis();
    nfc.reset();
  }
}