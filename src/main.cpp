#include <Arduino.h>
#include "tipos.h"
#include "logica/interfaz/entrada.h"
#include "logica/interfaz/pantalla.h"
#include "logica/interfaz/productos.h"
#include "logica/pagos/pagos.h"
#include "solidos/solidos.h"
#include "liquidos/liquidos.h"

Mode currentMode = MODE_MENU;
bool dirty = true;

// Función que manda a actualizar la pantalla solo cuando hubo algún cambio
void draw() {
  if (!dirty) return;
  dirty = false;

  dibujarPantalla(
    currentMode,
    obtenerNombreActual(),
    obtenerPrecioActual(),
    obtenerMontoRecarga(),
    obtenerSaldoTarjeta()
  );
}

// Decide qué hacer cuando se presiona un botón (0=P1, 1=P2, 2=P3, 3=P4)
void handleButton(uint8_t i) {
  if (currentMode == MODE_MENU) {
    if (i == 0) { 
      siguienteProducto();
    } else if (i == 1) { 
      reiniciarRecarga();
      currentMode = MODE_ADD_AMOUNT;
    }
  } else if (currentMode == MODE_ADD_AMOUNT) {
    if (i == 1) { 
      sumar500();
    } else if (i == 2) { 
      currentMode = MODE_READY_TO_READ;
    } else if (i == 3) { 
      currentMode = MODE_MENU;
    }
  } else if (currentMode == MODE_READY_TO_READ) {
    if (i == 0) { 
      currentMode = MODE_PAY_CHOICES;
    } else if (i == 3) { 
      currentMode = MODE_MENU;
    }
  } else if (currentMode == MODE_PAY_CHOICES) {
    if (i == 0) { 
      uint32_t price = obtenerPrecioActual();
      if (intentarCobrar(price)) {
        currentMode = MODE_RESULT_PAY;
      } else {
        mostrarSaldoInsuficiente();
        currentMode = MODE_PAY_CHOICES;
      }
    } else if (i == 1) { 
      currentMode = MODE_TAP_FOR_NFC;
      dirty = true;
      draw();
      delay(1500); 
      currentMode = MODE_NFC_SUCCESS;
    } else if (i == 3) { 
      currentMode = MODE_MENU;
    }
  } else if (currentMode == MODE_REFUND_OR_LEAVE) {
    if (i == 2) { 
      bool habiaSaldo = devolverSaldo();
      mostrarResultadoDevolucion(habiaSaldo);
      currentMode = MODE_MENU;
    } else if (i == 3) { 
      currentMode = MODE_MENU;
      mostrarSaldoAcumulado();
    }
  } else if (currentMode == MODE_NFC_SUCCESS) {
    if (i == 3) { 
      currentMode = MODE_MENU;
      mostrarGracias();
    }
  }
  dirty = true;
}

void setup() {
  Serial.begin(115200);
  configurarBotones();
  iniciarSolidos();
  iniciarLiquidos();
  iniciarPantalla();

  currentMode = MODE_MENU;
  dirty = true;
}

void loop() {
  // 1. Revisar si alguien presionó un botón
  int boton = leerBotonPresionado();
  if (boton != -1) {
    handleButton(boton);
  }

  // 2. Actualizar la pantalla si hace falta
  draw();
  
  // 3. Si acaba de pagar, esperar 3 segundos y pasar a la pantalla de devolución
  if (currentMode == MODE_RESULT_PAY) {
    delay(3000);
    currentMode = MODE_REFUND_OR_LEAVE;
    dirty = true;
  }
}
