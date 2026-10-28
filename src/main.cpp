#include <Arduino.h>
#include "tipos.h"
#include "herramientas/pantalla.h"
#include "herramientas/entrada.h"

Modo modoActual = MODO_BIENVENIDA;

void setup() {
  Serial.begin(115200);
  iniciarPantalla();
  iniciarEntradas();

  mostrarLineas("   DUALVEND!    ", "P1 para Iniciar ");
}

void loop() {
  // 1. Leer pulsadores de acción
  Boton boton = leerPulsador();
  if (boton != BOTON_NINGUNO) {
    if (boton == BOTON_P1) {
      Serial.println(F("Pulsador P1 presionado"));
      mostrarLineas("P1 Presionado   ", "Iniciando flujo ");
    } else if (boton == BOTON_P2) {
      Serial.println(F("Pulsador P2 presionado"));
      mostrarLineas("P2 Presionado   ", "Accion Siguiente");
    } else if (boton == BOTON_P3) {
      Serial.println(F("P3 Presionado"));
      mostrarLineas("P3 Presionado   ", "Accion Confirmar");
    } else if (boton == BOTON_PEXT) {
      Serial.println(F("PEXT Presionado (Cancelacion)"));
      mostrarLineas("CANCELADO (PEXT)", "Volviendo inicio");
      delay(1500);
      mostrarLineas("   DUALVEND!    ", "P1 para Iniciar ");
    }
  }

  // 2. Leer teclado matricial 4x4
  char tecla = leerTeclado();
  if (tecla != '\0') {
    Serial.print(F("Tecla presionada: "));
    Serial.println(tecla);
    
    char linea2[17];
    snprintf(linea2, sizeof(linea2), "Tecla: [ %c ]    ", tecla);
    mostrarLineas("Teclado 4x4 OK  ", linea2);
  }
}
