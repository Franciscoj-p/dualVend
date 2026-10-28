#ifndef PAGOS_H
#define PAGOS_H

#include <Arduino.h>

// Pone en 0 el monto que se va a recargar
void reiniciarRecarga();

// Suma $500 al monto de recarga (si pasa de 20.000 vuelve a 0)
void sumar500();

// Intenta cobrar el precio del producto. Devuelve true si alcanzó el saldo, false si no.
bool intentarCobrar(uint32_t precio);

// Devuelve el saldo restante (lo pone en 0). Devuelve true si había saldo, false si estaba en 0.
bool devolverSaldo();

// Funciones para consultar los valores actuales y mostrarlos en pantalla
uint32_t obtenerMontoRecarga();
uint32_t obtenerSaldoTarjeta();

#endif

