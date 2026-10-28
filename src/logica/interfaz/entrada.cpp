#include "entrada.h"

// Pines de los 4 botones
const uint8_t P1 = 3; 
const uint8_t P2 = 4; 
const uint8_t P3 = 5; 
const uint8_t P4 = 6; 

const uint8_t pins[] = {P1, P2, P3, P4}; 
uint8_t stable[4] = {HIGH, HIGH, HIGH, HIGH};
uint8_t lastReading[4] = {HIGH, HIGH, HIGH, HIGH};
unsigned long changedAt[4] = {0, 0, 0, 0};

void configurarBotones() {
  for (uint8_t i = 0; i < 4; i++) {
    pinMode(pins[i], INPUT_PULLUP);
  }
}

int leerBotonPresionado() {
  for (uint8_t idx = 0; idx < 4; idx++) {
    uint8_t registry = digitalRead(pins[idx]);
    if (registry != lastReading[idx]) { 
      lastReading[idx] = registry; 
      changedAt[idx] = millis(); 
    }
    if (millis() - changedAt[idx] >= 35 && stable[idx] != registry) {
      stable[idx] = registry;
      if (registry == LOW) {
        return idx; // Devuelve 0, 1, 2 o 3 según el botón presionado
      }
    }
  }
  return -1; // Ningún botón presionado
}

