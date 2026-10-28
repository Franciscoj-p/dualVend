#ifndef SOLIDOS_H
#define SOLIDOS_H

#include <Arduino.h>

// Configura pines de motores de resortes y microswitches (Grupo Sólidos)
void iniciarSolidos();

// Activa el motor de la espiral para entregar el snack
bool dispensarSolido(uint8_t producto);

#endif

