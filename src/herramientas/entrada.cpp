#include "entrada.h"
#include <Keypad.h>

// --- CONFIGURACIÓN DEL TECLADO MATRICIAL 4X4 ---
const byte FILAS = 4;
const byte COLUMNAS = 4;

char teclas[FILAS][COLUMNAS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pinesFilas[FILAS] = {6, 7, 8, 9};
byte pinesColumnas[COLUMNAS] = {10, 11, 12, 13};

static Keypad teclado = Keypad(makeKeymap(teclas), pinesFilas, pinesColumnas, FILAS, COLUMNAS);

// --- CONFIGURACIÓN DE LOS 4 PULSADORES ---
const uint8_t PIN_P1   = 2;
const uint8_t PIN_P2   = 3;
const uint8_t PIN_P3   = 4;
const uint8_t PIN_PEXT = 5;

const uint8_t pinesBotones[4] = {PIN_P1, PIN_P2, PIN_P3, PIN_PEXT};
static uint8_t estadosEstables[4] = {HIGH, HIGH, HIGH, HIGH};
static uint8_t ultimasLecturas[4] = {HIGH, HIGH, HIGH, HIGH};
static unsigned long ultimoCambio[4] = {0, 0, 0, 0};

void iniciarEntradas() {
  for (uint8_t i = 0; i < 4; i++) {
    pinMode(pinesBotones[i], INPUT_PULLUP);
    estadosEstables[i] = HIGH;
    ultimasLecturas[i] = HIGH;
    ultimoCambio[i] = 0;
  }
}

char leerTeclado() {
  char tecla = teclado.getKey();
  return (tecla) ? tecla : '\0';
}

Boton leerPulsador() {
  for (uint8_t idx = 0; idx < 4; idx++) {
    uint8_t lectura = digitalRead(pinesBotones[idx]);
    
    if (lectura != ultimasLecturas[idx]) {
      ultimasLecturas[idx] = lectura;
      ultimoCambio[idx] = millis();
    }
    
    if ((millis() - ultimoCambio[idx] >= 35) && (estadosEstables[idx] != lectura)) {
      estadosEstables[idx] = lectura;
      if (lectura == LOW) {
        switch (idx) {
          case 0: return BOTON_P1;
          case 1: return BOTON_P2;
          case 2: return BOTON_P3;
          case 3: return BOTON_PEXT;
          default: return BOTON_NINGUNO;
        }
      }
    }
  }
  return BOTON_NINGUNO;
}

