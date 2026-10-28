#ifndef ENTRADA_H
#define ENTRADA_H

#include <Arduino.h>
#include "../tipos.h"

// Configura los pines de los pulsadores y del teclado matricial 4x4
void iniciarEntradas();

// Lee si se presionó alguna tecla en el teclado matricial 4x4
// Devuelve: '0'..'9', 'A'..'D', '*', '#' o '\0' si no hay tecla
char leerTeclado();

// Lee si se presionó algún pulsador con antirrebote
// Devuelve: BOTON_P1, BOTON_P2, BOTON_P3, BOTON_PEXT o BOTON_NINGUNO
Boton leerPulsador();

#endif
