#include "pantalla.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pantalla LCD 20x4 I2C en dirección 0x27
static LiquidCrystal_I2C lcd(0x27, 20, 4);

void iniciarPantalla() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void mostrarLineas(const char* l1, const char* l2, const char* l3, const char* l4) {
  lcd.clear();
  
  if (l1 != nullptr && l1[0] != '\0') {
    lcd.setCursor(0, 0);
    lcd.print(l1);
  }
  
  if (l2 != nullptr && l2[0] != '\0') {
    lcd.setCursor(0, 1);
    lcd.print(l2);
  }

  if (l3 != nullptr && l3[0] != '\0') {
    lcd.setCursor(0, 2);
    lcd.print(l3);
  }

  if (l4 != nullptr && l4[0] != '\0') {
    lcd.setCursor(0, 3);
    lcd.print(l4);
  }
}

void limpiarPantalla() {
  lcd.clear();
}

void mostrarMensajeTemporal(const char* l1, const char* l2, unsigned int tiempoMs, const char* l3, const char* l4) {
  mostrarLineas(l1, l2, l3, l4);
  delay(tiempoMs);
}
