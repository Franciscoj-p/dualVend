#ifndef PAGOS_H
#define PAGOS_H

#include <Arduino.h>
#include "tipos.h"

/**
 * ==============================================================================
 * CONTRATO DEL MÓDULO DE PAGOS (src/logica/pagos/)
 * ==============================================================================
 * A cargo del: Integrante de Pagos
 * 
 * ¿Qué recibe de Selección / main.cpp?
 * - iniciarPago(uint32_t montoTotal): Recibe el monto exacto en pesos que el
 *   cliente debe pagar según los productos acumulados en el carrito.
 * 
 * ¿Qué debe hacer adentro de procesarPago(boton, tecla)?
 * - Controlar la pantalla LCD 16x2 mostrando el total y el saldo ingresado.
 * - Leer los sensores o lectores de pago (monedero, billetero, lector RFID/NFC, etc.).
 * - Gestionar el saldo acumulado del usuario.
 * 
 * ¿Qué debe devolver a main.cpp?
 * - PAGO_EN_CURSO: El cliente aún no ha completado el valor requerido.
 * - PAGO_EXITOSO: El cliente cubrió la totalidad del dinero. main.cpp pasará
 *   a la entrega física de productos.
 * - PAGO_CANCELADO: El cliente canceló o se agotó el tiempo. main.cpp devolverá
 *   la máquina a la pantalla de bienvenida.
 * ==============================================================================
 */

// Inicia la sesión de cobro con el total a pagar en pesos
void iniciarPago(uint32_t montoTotal);

// Procesa un ciclo de cobro (lee sensores/entradas, actualiza LCD)
ResultadoPago procesarPago(Boton boton, char tecla);

// Funciones de consulta útiles para pruebas
uint32_t obtenerMontoTotalACobrar();
uint32_t obtenerSaldoIngresado();

#endif
