#ifndef LIQUIDOS_H
#define LIQUIDOS_H

#include <Arduino.h>

// Configura pines de bomba peristáltica, electroválvula y caudalímetro (Grupo Líquidos)
void iniciarLiquidos();

// Activa la bomba dosificadora para servir la bebida
bool dispensarLiquido(uint8_t producto);

#endif

