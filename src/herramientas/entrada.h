#ifndef ENTRADA_H
#define ENTRADA_H

#include <Arduino.h>
#include "../tipos.h"

// Inicializa las entradas (teclado matricial 4x4)
void iniciarEntradas();

// Lee la tecla presionada en el teclado matricial 4x4 ('0'..'9', 'A'..'D', '*', '#' o '\0')
char leerTeclado();

// Detecta si la tecla presionada corresponde a una acción de botón (A, B, C, D o '#')
// Devuelve: BOTON_A, BOTON_B, BOTON_C, BOTON_D o BOTON_NINGUNO
Boton leerPulsador();

#endif
