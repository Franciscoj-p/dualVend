#include <Arduino.h>
#include "tipos.h"
#include "datos/inventario.h"
#include "herramientas/pantalla.h"
#include "herramientas/entrada.h"
#include "logica/seleccion/seleccion.h"
#include "logica/pagos/pagos.h"
#include "solidos/solidos.h"
#include "liquidos/liquidos.h"

// Modo activo de la máquina de estados
static Modo modoActual = MODO_BIENVENIDA;
static bool pantallaBienvenidaLista = false;

// Realiza la entrega física de cada producto en el carrito (Sólidos o Líquidos)
static void ejecutarEntregaProductos() {
  uint8_t total = obtenerTotalProductos();
  for (uint8_t i = 0; i < total; i++) {
    Producto* p = obtenerProductoPorIndice(i);
    if (p != nullptr && p->enCarrito > 0) {
      for (uint8_t c = 0; c < p->enCarrito; c++) {
        if (p->tipo == TIPO_SOLIDO) {
          dispensarSolido(p->nombre);
        } else if (p->tipo == TIPO_LIQUIDO) {
          dispensarLiquido(p->nombre);
        }
      }
    }
  }
  // Una vez entregado todo, se descuenta del inventario y se despide
  descontarStockVendido();
  mostrarMensajeTemporal("====================", "   MUCHAS GRACIAS   ", 1800, "  POR SU COMPRA!    ", "====================");
}

void setup() {
  Serial.begin(115200);

  // Inicialización de hardware compartido
  iniciarPantalla();
  iniciarEntradas();

  // Inicialización de datos e inventario
  iniciarInventario();

  // Inicialización de periféricos mecánicos
  iniciarSolidos();
  iniciarLiquidos();

  modoActual = MODO_BIENVENIDA;
  pantallaBienvenidaLista = false;
  Serial.println(F("[SISTEMA] DualVend listo para operar con LCD 20x4"));
}

void loop() {
  // 1. Lectura de periféricos de entrada compartidos
  Boton boton = leerPulsador();
  char tecla = leerTeclado();

  // 2. BOTÓN DE CANCELACIÓN GLOBAL (PEXT)
  if (boton == BOTON_PEXT) {
    if (modoActual != MODO_BIENVENIDA) {
      Serial.println(F("[PEXT] Operacion cancelada por el usuario"));
      mostrarMensajeTemporal(" OPERACION CANCEL.  ", " Devolviendo saldo  ", 1500, " Retire su dinero   ", " Vuelva a intentar  ");
      vaciarCarrito();
      modoActual = MODO_BIENVENIDA;
      pantallaBienvenidaLista = false;
      return;
    }
  }

  // 3. DIRECTOR DE ESTADOS (FSM)
  switch (modoActual) {
    
    // --- ESTADO 1: BIENVENIDA ---
    case MODO_BIENVENIDA:
      if (!pantallaBienvenidaLista) {
        mostrarLineas("********************",
                      "    DUALVEND 2.0    ",
                      "  Snacks & Bebidas  ",
                      " P1: Iniciar Compra ");
        pantallaBienvenidaLista = true;
      }
      if (boton == BOTON_P1) {
        vaciarCarrito();
        iniciarSeleccion();
        modoActual = MODO_SELECCION;
        pantallaBienvenidaLista = false;
      }
      break;

    // --- ESTADO 2: SELECCIÓN DE PRODUCTOS (Módulo Selección) ---
    case MODO_SELECCION:
      if (procesarSeleccion(boton, tecla) == SELECCION_LISTO_IR_A_PAGOS) {
        iniciarPago(calcularTotalCarrito());
        modoActual = MODO_COBRO;
      }
      break;

    // --- ESTADO 3: COBRO Y RECEPCIÓN DE DINERO (Módulo Pagos) ---
    case MODO_COBRO:
      if (procesarPago(boton, tecla) == PAGO_EXITOSO) {
        modoActual = MODO_ENTREGA;
      }
      break;

    // --- ESTADO 4: ENTREGA FÍSICA Y DESCUENTO DE STOCK ---
    case MODO_ENTREGA:
      ejecutarEntregaProductos();
      modoActual = MODO_BIENVENIDA;
      pantallaBienvenidaLista = false;
      break;
  }
}
