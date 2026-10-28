#include "pantalla.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pantalla LCD 16x2 I2C en la dirección 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

void iniciarPantalla() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(F("Iniciando..."));
  delay(1000);
}

void dibujarPantalla(Mode currentMode, const char* nombreProd, uint32_t precioProd, uint32_t amountToAdd, uint32_t currentCardBalance) {
  lcd.clear();

  if (currentMode == MODE_MENU) {
    lcd.setCursor(0, 0);
    lcd.print(nombreProd);
    lcd.print(F("  $"));
    lcd.print(precioProd);
    lcd.setCursor(0, 1);
    lcd.print(F("P1:Prod P2:Recarg"));
  } else if (currentMode == MODE_ADD_AMOUNT) {
    lcd.setCursor(0, 0);
    lcd.print(F("Recargar: +$"));
    lcd.print(amountToAdd);
    lcd.setCursor(0, 1);
    lcd.print(F("P2:+500 P3:Conf"));
  } else if (currentMode == MODE_READY_TO_READ) {
    lcd.setCursor(0, 0);
    lcd.print(F("Monto: $"));
    lcd.print(amountToAdd);
    lcd.setCursor(0, 1);
    lcd.print(F("P1: Pagar"));
  } else if (currentMode == MODE_PAY_CHOICES) {
    lcd.setCursor(0, 0);
    lcd.print(F("P1:Pagar Saldo"));
    lcd.setCursor(0, 1);
    lcd.print(F("P2:Pago NFC"));
  } else if (currentMode == MODE_TAP_FOR_NFC) {
    lcd.setCursor(0, 0);
    lcd.print(F("Pago NFC Directo"));
    lcd.setCursor(0, 1);
    lcd.print(F("Simulando pago..."));
  } else if (currentMode == MODE_RESULT_PAY) {
    lcd.setCursor(0, 0);
    lcd.print(F("Pago exitoso!"));
    lcd.setCursor(0, 1);
    lcd.print(F("Restante: $"));
    lcd.print(currentCardBalance);
  } else if (currentMode == MODE_REFUND_OR_LEAVE) {
    lcd.setCursor(0, 0);
    lcd.print(F("P3:Devolver saldo"));
    lcd.setCursor(0, 1);
    lcd.print(F("P4:Salir (Acum)"));
  } else if (currentMode == MODE_NFC_SUCCESS) {
    lcd.setCursor(0, 0);
    lcd.print(F("Pago exitoso"));
    lcd.setCursor(0, 1);
    lcd.print(F("P4: Salir"));
  }
}

void mostrarSaldoInsuficiente() {
  lcd.clear();
  lcd.print(F("Saldo insufic."));
  delay(1500);
}

void mostrarResultadoDevolucion(bool habiaSaldo) {
  lcd.clear();
  if (!habiaSaldo) {
    lcd.print(F("Sin saldo para"));
    lcd.setCursor(0, 1);
    lcd.print(F("devolver"));
  } else {
    lcd.print(F("Saldo devuelto"));
    lcd.setCursor(0, 1);
    lcd.print(F("exitosamente"));
  }
  delay(2500);
}

void mostrarSaldoAcumulado() {
  lcd.clear();
  lcd.print(F("Saldo acumulado"));
  lcd.setCursor(0, 1);
  lcd.print(F("Guardado en tarj"));
  delay(2500);
}

void mostrarGracias() {
  lcd.clear();
  lcd.print(F("Gracias!"));
  delay(2000);
}

