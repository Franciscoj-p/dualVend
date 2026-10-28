#ifndef PANTALLA_H
#define PANTALLA_H

#include <Arduino.h>
#include "../../tipos.h"

// Inicializa la pantalla LCD 16x2 I2C y muestra "Iniciando..."
void iniciarPantalla();

// Dibuja la pantalla según el modo actual
void dibujarPantalla(Mode currentMode, const char* nombreProd, uint32_t precioProd, uint32_t amountToAdd, uint32_t currentCardBalance);

// Mensajes de aviso que usa la máquina
void mostrarSaldoInsuficiente();
void mostrarResultadoDevolucion(bool habiaSaldo);
void mostrarSaldoAcumulado();
void mostrarGracias();

#endif

