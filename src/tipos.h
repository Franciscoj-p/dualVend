#ifndef TIPOS_H
#define TIPOS_H

#include <Arduino.h>

// Botones y acciones del sistema
// Ahora corresponden a las teclas A, B, C, D del teclado matricial 4x4
enum Boton {
  BOTON_NINGUNO = 0,
  BOTON_A,          // Tecla A: Iniciar / Anterior / Agregar otro
  BOTON_B,          // Tecla B: Siguiente producto
  BOTON_C,          // Tecla C: Confirmar producto / Pagar (también tecla '#')
  BOTON_D,          // Tecla D: Cancelar / Abortar operación (reemplaza Pext)

  // Alias para mantener compatibilidad con apuntes y versiones anteriores:
  BOTON_P1 = BOTON_A,
  BOTON_P2 = BOTON_B,
  BOTON_P3 = BOTON_C,
  BOTON_PEXT = BOTON_D
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
