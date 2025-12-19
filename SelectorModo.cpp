//selectormodo.cpp
#include "SelectorModo.h"

SelectorModo::SelectorModo(byte p) : pin(p) {
  pinMode(pin, INPUT_PULLUP);
}

bool SelectorModo::esKiosko() const {
  return digitalRead(pin) == HIGH;
}
