#include <Arduino.h>
#include "tipos.h"
#include "herramientas/pantalla.h"
#include "herramientas/entrada.h"
#include "logica/seleccion/seleccion.h"

Modo modoActual = MODO_BIENVENIDA;
bool pantallaSucia = true;

// Dibuja en la pantalla LCD 16x2 según el modo actual de la máquina
void actualizarPantalla() {
  if (!pantallaSucia) return;
  pantallaSucia = false;

  char linea1[17];
  char linea2[17];

  switch (modoActual) {
    case MODO_BIENVENIDA:
      mostrarLineas("   DUALVEND!    ", "P1 para Iniciar ");
      break;

    case MODO_SELECCION:
      // Línea 1: Cod:[01]  $1000
      snprintf(linea1, sizeof(linea1), "Cod:%-2s   $%5lu", 
               obtenerCodigoActual(), 
               (unsigned long)obtenerPrecioActual());
      
      // Línea 2: Papas   Disp:5
      snprintf(linea2, sizeof(linea2), "%-9s Disp:%-2u", 
               obtenerNombreActual(), 
               obtenerStockDisponibleActual());
      
      mostrarLineas(linea1, linea2);
      break;

    case MODO_PREGUNTA_CARRITO:
      // Línea 1: Total: $3500
      snprintf(linea1, sizeof(linea1), "Total: $%7lu", 
               (unsigned long)obtenerTotalCarrito());
      
      // Línea 2: P1:+Otro P3:Pagar
      mostrarLineas(linea1, "P1:+Otro P3:Pagar");
      break;

    case MODO_COBRO:
      // Línea 1: A Pagar: $3500
      snprintf(linea1, sizeof(linea1), "Cobro: $%7lu", 
               (unsigned long)obtenerTotalCarrito());
      mostrarLineas(linea1, "P3:Simular Pago ");
      break;

    case MODO_ENTREGA:
      mostrarLineas("  DISPENSANDO   ", "Gracias x compra");
      break;
  }
}

void setup() {
  Serial.begin(115200);
  iniciarPantalla();
  iniciarEntradas();
  iniciarSeleccion();

  modoActual = MODO_BIENVENIDA;
  pantallaSucia = true;
}

void loop() {
  // 1. Leer pulsadores frontales
  Boton boton = leerPulsador();
  
  // 2. Leer teclado matricial 4x4
  char tecla = leerTeclado();

  // --- BOTÓN DE CANCELACIÓN GLOBAL (PEXT) ---
  if (boton == BOTON_PEXT) {
    if (modoActual != MODO_BIENVENIDA) {
      Serial.println(F("[PEXT] Operacion cancelada"));
      mostrarMensajeTemporal("OPERACION CANC. ", "Devolviendo saldo", 1500);
      vaciarCarrito();
      modoActual = MODO_BIENVENIDA;
      pantallaSucia = true;
      return;
    }
  }

  // --- MÁQUINA DE ESTADOS FINITOS (FSM) ---
  switch (modoActual) {
    
    // --- ESTADO 1: BIENVENIDA ---
    case MODO_BIENVENIDA:
      if (boton == BOTON_P1) {
        Serial.println(F("Iniciando seleccion de producto..."));
        vaciarCarrito();
        modoActual = MODO_SELECCION;
        pantallaSucia = true;
      }
      break;

    // --- ESTADO 2: SELECCIÓN DE PRODUCTO ---
    case MODO_SELECCION:
      // Entrada por teclado matricial (marcar código numérico)
      if (tecla >= '0' && tecla <= '9') {
        Serial.print(F("Digito tecleado: "));
        Serial.println(tecla);
        procesarTeclaCodigo(tecla);
        pantallaSucia = true;
      } else if (tecla == '#') {
        // '#' en el teclado equivale a P3 (confirmar)
        boton = BOTON_P3;
      }

      // Navegación con pulsadores
      if (boton == BOTON_P1) {
        anteriorProducto();
        pantallaSucia = true;
      } else if (boton == BOTON_P2) {
        siguienteProducto();
        pantallaSucia = true;
      } else if (boton == BOTON_P3) {
        // Confirmar producto y agregar al pedido
        if (agregarProductoAlCarrito()) {
          Serial.print(F("Producto agregado: "));
          Serial.println(obtenerNombreActual());
          mostrarMensajeTemporal("Agregado al Ped!", obtenerNombreActual(), 1000);
          modoActual = MODO_PREGUNTA_CARRITO;
        } else {
          Serial.println(F("Stock agotado para este producto"));
          mostrarMensajeTemporal("Sin Stock Disp! ", "Elija otro...   ", 1500);
        }
        pantallaSucia = true;
      }
      break;

    // --- ESTADO 2.1: PREGUNTA DEL CARRITO (¿PEDIR OTRO O PAGAR?) ---
    case MODO_PREGUNTA_CARRITO:
      if (boton == BOTON_P1) {
        // P1: Desea pedir otro producto más
        Serial.println(F("Pidiendo otro producto..."));
        modoActual = MODO_SELECCION;
        pantallaSucia = true;
      } else if (boton == BOTON_P3) {
        // P3: Terminar selección e ir a Cobro
        Serial.print(F("Finalizando seleccion. Total a cobrar: $"));
        Serial.println(obtenerTotalCarrito());
        modoActual = MODO_COBRO;
        pantallaSucia = true;
      }
      break;

    // --- ESTADO 3: COBRO (ESPERANDO A PAGOS) ---
    case MODO_COBRO:
      // Simulación de cobro (a la espera del hardware de Pagos)
      // Pulsar P3 simula el pago completado
      if (boton == BOTON_P3) {
        Serial.println(F("Pago aprobado exitosamente"));
        mostrarMensajeTemporal(" Pago Exitoso!  ", " Despachando... ", 1500);
        modoActual = MODO_ENTREGA;
        pantallaSucia = true;
      }
      break;

    // --- ESTADO 4: ENTREGA FÍSICA Y DESCUENTO DE STOCK ---
    case MODO_ENTREGA:
      Serial.println(F("Dispensando productos y descontando stock..."));
      descontarStockVendido();
      delay(2000);
      mostrarMensajeTemporal("   DUALVEND!    ", "Vuelva pronto   ", 1500);
      modoActual = MODO_BIENVENIDA;
      pantallaSucia = true;
      break;
  }

  // Refrescar pantalla LCD
  actualizarPantalla();
}
