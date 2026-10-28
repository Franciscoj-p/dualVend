#include "pantalla.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pantalla LCD 16x2 I2C en dirección 0x27
static LiquidCrystal_I2C lcd(0x27, 16, 2);

void iniciarPantalla() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void mostrarLineas(const char* linea1, const char* linea2) {
  lcd.clear();
  
  if (linea1 != nullptr) {
    lcd.setCursor(0, 0);
    lcd.print(linea1);
  }
  
  if (linea2 != nullptr) {
    lcd.setCursor(0, 1);
    lcd.print(linea2);
  }
}

void limpiarPantalla() {
  lcd.clear();
}

void mostrarMensajeTemporal(const char* linea1, const char* linea2, unsigned int tiempoMs) {
  mostrarLineas(linea1, linea2);
  delay(tiempoMs);
}

