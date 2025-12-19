//transporte.h
#ifndef SISTEMA_TRANSPORTE_H
#define SISTEMA_TRANSPORTE_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Arduino.h>
#include <RTClib.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_PN532.h>

class PantallaLCD {
private:
  LiquidCrystal_I2C lcd;
public:
  PantallaLCD();
  void iniciar();
  void mensaje(const String& l1, const String& l2 = "");
};

class Buzzer {
private:
  byte pin;
  byte canal;
  bool iniciado;
public:
  Buzzer(byte p, byte c = 0);
  void iniciar();
  void ok();
  void error();
};

class Reloj {
private:
RTC_DS3231 rtc;
bool iniciado; 
public:
  Reloj();
  void iniciar();
  void ahora(String& fecha, String& hora);
};

class Tarjeta {
protected:
  String uid;
  float saldo;

public:
  Tarjeta(const String& id, float s);
  virtual ~Tarjeta();

  String getUID() const;
  float getSaldo() const;

  void recargar(float monto);
  bool cobrar(float monto);

  virtual String tipo() const = 0;
};

class TarjetaComun : public Tarjeta {
public:
  TarjetaComun(const String& id, float s);
  String tipo() const override;
};

class TarjetaEstudiante : public Tarjeta {
public:
  TarjetaEstudiante(const String& id, float s);
  String tipo() const override;
};

class TarjetaAdultoMayor : public Tarjeta {
public:
  TarjetaAdultoMayor(const String& id, float s);
  String tipo() const override;
};

class AlmacenSD {
private:
  byte cs;
  bool iniciado;
public:
  AlmacenSD(byte pinCS);
  void iniciar();
  Tarjeta* cargarTarjeta(const String& uid);
  void guardarTarjeta(Tarjeta* t);
  void guardarOperacion(const String& linea);
};

class LectorNFC {
private:
  Adafruit_PN532 nfc;
  bool iniciado;
  String ultimoUID;
public:
  LectorNFC(byte sda, byte scl);
  void iniciar();
  bool leerUID(String& uid);
  void reset();
};

#endif
