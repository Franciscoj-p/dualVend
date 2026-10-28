#ifndef TIPOS_H
#define TIPOS_H

#include <Arduino.h>

// Pulsadores físicos del sistema
enum Boton {
  BOTON_NINGUNO = 0,
  BOTON_P1,          // Pulsador 1 (Iniciar / Anterior / Pedir otro)
  BOTON_P2,          // Pulsador 2 (Siguiente)
  BOTON_P3,          // Pulsador 3 (Confirmar producto / Ir a pagar)
  BOTON_PEXT         // Pulsador externo de cancelación/aborto general
};

// Modos de la máquina de estados (FSM)
enum Modo {
  MODO_BIENVENIDA,        // Pantalla de reposo
  MODO_SELECCION,         // Viendo producto por código / teclado / botones
  MODO_PREGUNTA_CARRITO,  // Pregunta: ¿Agregar otro producto o ir a pagar?
  MODO_COBRO,             // Entregado a Pagos con el monto total acumulado
  MODO_ENTREGA            // Dispensación física de snacks y bebidas
};

#endif
