#include "pagos.h"

// Variables de dinero
uint32_t amountToAdd = 0;
uint32_t currentCardBalance = 0;
uint32_t lastPaidPrice = 0;

void reiniciarRecarga() {
  amountToAdd = 0;
}

void sumar500() {
  amountToAdd += 500;
  if (amountToAdd > 20000) {
    amountToAdd = 0;
  }
}

bool intentarCobrar(uint32_t precio) {
  if (amountToAdd >= precio) {
    amountToAdd -= precio;
    currentCardBalance = amountToAdd;
    lastPaidPrice = precio;
    return true; // Pago aprobado
  }
  return false;  // Saldo insuficiente
}

bool devolverSaldo() {
  if (currentCardBalance == 0) {
    return false; // No había nada que devolver
  }
  currentCardBalance = 0;
  amountToAdd = 0;
  return true;    // Saldo devuelto con éxito
}

uint32_t obtenerMontoRecarga() {
  return amountToAdd;
}

uint32_t obtenerSaldoTarjeta() {
  return currentCardBalance;
}

