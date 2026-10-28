#ifndef SELECCION_H
#define SELECCION_H

#include <Arduino.h>
#include "tipos.h"

/**
 * ==============================================================================
 * MÓDULO DE SELECCIÓN DE PRODUCTOS (src/logica/seleccion/)
 * ==============================================================================
 * Responsabilidad:
 * - Mostrar en el LCD 16x2 el catálogo de productos con precios y stock.
 * - Permitir la navegación con pulsadores (P1 anterior, P2 siguiente).
 * - Permitir la marcación directa por teclado matricial ("01", "02", etc.).
 * - Gestionar el carrito de compras y preguntar si desea agregar otro producto.
 * 
 * Contrato con main.cpp:
 * - iniciarSeleccion(): Prepara el estado interno y la pantalla al entrar al modo.
 * - procesarSeleccion(boton, tecla): Se ejecuta en cada ciclo de loop() mientras
 *   modoActual == MODO_SELECCION. Dibuja su propia interfaz y devuelve:
 *     - SELECCION_EN_CURSO: El cliente sigue navegando.
 *     - SELECCION_LISTO_IR_A_PAGOS: El cliente terminó y pasa a Cobro.
 *     - SELECCION_CANCELADA: El cliente canceló la operación.
 * ==============================================================================
 */

// Inicializa el módulo de selección (cursor en producto 0, pantalla lista)
void iniciarSeleccion();

// Procesa un ciclo de selección con las entradas actuales
ResultadoSeleccion procesarSeleccion(Boton boton, char tecla);

#endif
