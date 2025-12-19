//selectormodo.h
#ifndef SELECTOR_MODO_H
#define SELECTOR_MODO_H

#include <Arduino.h>

class SelectorModo {
private:
  byte pin;

public:
  SelectorModo(byte p);
  bool esKiosko() const;
};

#endif
