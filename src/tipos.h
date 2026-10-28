#ifndef TIPOS_H
#define TIPOS_H

#include <Arduino.h>

// Pulsadores físicos del sistema
enum Boton {
  BOTON_NINGUNO = 0,
  BOTON_P1,          // Pulsador 1 (Acción primaria / Iniciar / Anterior / Agregar otro)
  BOTON_P2,          // Pulsador 2 (Siguiente)
  BOTON_P3,          // Pulsador 3 (Confirmar producto / Ir a Pagar)
  BOTON_PEXT         // Pulsador externo (Cancelar / Abortar en cualquier momento)
};

// Estados generales de la máquina de estados finitos (FSM en main.cpp)
enum Modo {
  MODO_BIENVENIDA,   // Pantalla de espera / reposo
  MODO_SELECCION,    // Módulo Selección: cliente navega y elige productos
  MODO_COBRO,        // Módulo Pagos: cliente ingresa dinero
  MODO_ENTREGA       // Módulo Dispensación: entrega física (Sólidos y Líquidos)
};

// Resultado que el módulo de Selección entrega al director (main.cpp)
enum ResultadoSeleccion {
  SELECCION_EN_CURSO,            // El usuario aún está navegando o eligiendo
  SELECCION_LISTO_IR_A_PAGOS,    // Confirmó su pedido y desea pagar
  SELECCION_CANCELADA            // El usuario canceló la selección
};

// Resultado que el módulo de Pagos entrega al director (main.cpp)
enum ResultadoPago {
  PAGO_EN_CURSO,     // Esperando que el usuario inserte dinero / acerque tarjeta
  PAGO_EXITOSO,      // Dinero cubierto por completo, listo para entregar
  PAGO_CANCELADO     // Cancelado o tiempo agotado, devolver saldo y reiniciar
};

#endif
