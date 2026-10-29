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

static char teclaActual = '\0';
static unsigned long ultimoMuestreo = 0;

static void muestrearTeclado() {
  unsigned long ahora = millis();
  if (ahora != ultimoMuestreo) {
    ultimoMuestreo = ahora;
    teclaActual = teclado.getKey();
  }
}

void iniciarEntradas() {
  teclaActual = '\0';
  ultimoMuestreo = 0;
}

char leerTeclado() {
  muestrearTeclado();
  return (teclaActual) ? teclaActual : '\0';
}

Boton leerPulsador() {
  muestrearTeclado();
  switch (teclaActual) {
    case 'A': return BOTON_A;
    case 'B': return BOTON_B;
    case 'C':
    case '#': return BOTON_C;
    case 'D': return BOTON_D;
    default:  return BOTON_NINGUNO;
  }
}
