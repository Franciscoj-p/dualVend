#ifndef TIPOS_H
#define TIPOS_H

#include <Arduino.h>

// Pulsadores físicos del sistema
enum Boton {
  BOTON_NINGUNO = 0,
  BOTON_P1,          // Pulsador 1
  BOTON_P2,          // Pulsador 2
  BOTON_P3,          // Pulsador 3
  BOTON_PEXT         // Pulsador externo de cancelación/aborto
};

// Modos principales de la máquina expendedora
enum Modo {
  MODO_BIENVENIDA,   // Pantalla inicial de bienvenida
  MODO_SELECCION,    // Selección de productos con código y carrito
  MODO_COBRO,        // Ingreso y cobro de saldo
  MODO_ENTREGA       // Activación de dispensadores físicos
};

#endif
