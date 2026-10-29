#include "seleccion.h"
#include "herramientas/pantalla.h"
#include "datos/inventario.h"

// Submodos internos de la experiencia de selección
enum SubmodoSeleccion {
  SUBMODO_CATALOGO,          // Viendo producto por código / teclado / botones
  SUBMODO_PREGUNTA_CARRITO   // Preguntando si desea agregar otro o ir a pagar
};

static SubmodoSeleccion submodo = SUBMODO_CATALOGO;
static uint8_t indiceActual = 0;
static char bufferCodigo[3] = {'0', '1', '\0'};
static uint8_t posBuffer = 0;
static bool pantallaSucia = true;

static void sincronizarCodigoConIndice() {
  Producto* p = obtenerProductoPorIndice(indiceActual);
  if (p != nullptr) {
    bufferCodigo[0] = p->codigo[0];
    bufferCodigo[1] = p->codigo[1];
    bufferCodigo[2] = '\0';
  }
  posBuffer = 0;
}

void iniciarSeleccion() {
  indiceActual = 0;
  submodo = SUBMODO_CATALOGO;
  sincronizarCodigoConIndice();
  pantallaSucia = true;
}

static void dibujarPantallaSeleccion() {
  if (!pantallaSucia) return;
  pantallaSucia = false;

  char linea1[21];
  char linea2[21];
  char linea3[21];
  char linea4[21];

  if (submodo == SUBMODO_CATALOGO) {
    Producto* p = obtenerProductoPorIndice(indiceActual);
    
    // Fila 0: Cabecera
    snprintf(linea1, sizeof(linea1), "== SELECCIONAR ==");

    // Fila 1: Cod:[01] Papas  $1000
    snprintf(linea2, sizeof(linea2), "Cod:[%-2s] %-7s$%5lu", 
             bufferCodigo, 
             p ? p->nombre : "???", 
             p ? (unsigned long)p->precio : 0UL);

    // Fila 2: Disp:5   En Pedido:0
    snprintf(linea3, sizeof(linea3), "Disp:%-2u   Carrito:%-2u", 
             obtenerStockDisponible(indiceActual),
             p ? p->enCarrito : 0);

    // Fila 3: Botones de ayuda
    snprintf(linea4, sizeof(linea4), "P1:Ant P2:Sig P3:Add");

    mostrarLineas(linea1, linea2, linea3, linea4);
  } 
  else if (submodo == SUBMODO_PREGUNTA_CARRITO) {
    snprintf(linea1, sizeof(linea1), "=== TU CARRITO ===");
    snprintf(linea2, sizeof(linea2), "Items: %-2u unidades", calcularCantidadTotalCarrito());
    snprintf(linea3, sizeof(linea3), "Total: $%7lu", (unsigned long)calcularTotalCarrito());
    snprintf(linea4, sizeof(linea4), "P1:+Otro    P3:Pagar");

    mostrarLineas(linea1, linea2, linea3, linea4);
  }
}

ResultadoSeleccion procesarSeleccion(Boton boton, char tecla) {
  // 1. Manejo en modo CATÁLOGO
  if (submodo == SUBMODO_CATALOGO) {
    // A. Marcación numérica en teclado matricial
    if (tecla >= '0' && tecla <= '9') {
      if (posBuffer == 0) {
        bufferCodigo[0] = tecla;
        bufferCodigo[1] = '-';
        posBuffer = 1;
        pantallaSucia = true;
      } else if (posBuffer == 1) {
        bufferCodigo[1] = tecla;
        posBuffer = 0;

        int8_t encontrado = buscarIndicePorCodigo(bufferCodigo);
        if (encontrado >= 0) {
          indiceActual = (uint8_t)encontrado;
        } else {
          // Si el código no existe, restaurar el código actual
          sincronizarCodigoConIndice();
        }
        pantallaSucia = true;
      }
    } 
    else if (tecla == '*') {
      // '*' cancela o resetea el código tecleado
      sincronizarCodigoConIndice();
      pantallaSucia = true;
    } 
    else if (tecla == '#') {
      // '#' equivale a presionar P3 (confirmar)
      boton = BOTON_P3;
    }

    // B. Navegación con pulsadores P1 y P2
    if (boton == BOTON_P1) {
      if (indiceActual == 0) {
        indiceActual = obtenerTotalProductos() - 1;
      } else {
        indiceActual--;
      }
      sincronizarCodigoConIndice();
      pantallaSucia = true;
    } 
    else if (boton == BOTON_P2) {
      indiceActual = (indiceActual + 1) % obtenerTotalProductos();
      sincronizarCodigoConIndice();
      pantallaSucia = true;
    } 
    // C. Confirmar producto con P3
    else if (boton == BOTON_P3) {
      if (agregarAlCarrito(indiceActual)) {
        Producto* p = obtenerProductoPorIndice(indiceActual);
        char msg[21];
        snprintf(msg, sizeof(msg), "+1 %s", p ? p->nombre : "");
        mostrarMensajeTemporal(" Producto Agregado! ", msg, 1200, "Agregado a tu pedido", "Espere un momento...");
        submodo = SUBMODO_PREGUNTA_CARRITO;
      } else {
        mostrarMensajeTemporal("  SIN STOCK DISP!   ", "  Elija otro item   ", 1500, "No quedan disponibles", "");
      }
      pantallaSucia = true;
    }
  }
  // 2. Manejo en modo PREGUNTA CARRITO
  else if (submodo == SUBMODO_PREGUNTA_CARRITO) {
    if (boton == BOTON_P1) {
      // Volver al catálogo para pedir otro producto
      submodo = SUBMODO_CATALOGO;
      sincronizarCodigoConIndice();
      pantallaSucia = true;
    } 
    else if (boton == BOTON_P3 || tecla == '#') {
      // Pedido confirmado, entregar control al director para pasar a Cobro
      return SELECCION_LISTO_IR_A_PAGOS;
    }
  }

  // Refrescar LCD si hubo cambios
  dibujarPantallaSeleccion();

  return SELECCION_EN_CURSO;
}
