#ifndef ENTRADA_H
#define ENTRADA_H

#include <Arduino.h>

// Configura los pines de los botones
void configurarBotones();

// Revisa si se presionó algún botón con antirrebote.
// Devuelve: 0 (P1), 1 (P2), 2 (P3), 3 (P4) o -1 si no se presionó ninguno.
int leerBotonPresionado();

#endif

