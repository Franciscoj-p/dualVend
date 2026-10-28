#include "seleccion.h"

const uint8_t TOTAL_PRODUCTOS = 3;

// Catálogo de productos (con códigos de 2 dígitos visibles en la máquina física)
static const char* codigos[TOTAL_PRODUCTOS] = {"01", "02", "03"};
static const char* nombres[TOTAL_PRODUCTOS] = {"Papas", "Galletas", "Gaseosa"};
static const uint16_t precios[TOTAL_PRODUCTOS] = {1000, 2500, 2000};

// Stock disponible en la máquina y cantidades pedidas en el carrito actual
static uint8_t stock[TOTAL_PRODUCTOS] = {5, 5, 5};
static uint8_t carrito[TOTAL_PRODUCTOS] = {0, 0, 0};

static uint8_t indiceActual = 0;
static char bufferCodigo[3] = {'-', '-', '\0'};
static uint8_t posBuffer = 0;

void iniciarSeleccion() {
  indiceActual = 0;
  bufferCodigo[0] = codigos[0][0];
  bufferCodigo[1] = codigos[0][1];
  bufferCodigo[2] = '\0';
  posBuffer = 0;
}

void procesarTeclaCodigo(char tecla) {
  // '*' cancela o resetea el código tecleado
  if (tecla == '*') {
    bufferCodigo[0] = codigos[indiceActual][0];
    bufferCodigo[1] = codigos[indiceActual][1];
    posBuffer = 0;
    return;
  }

  // Si es un número '0'..'9'
  if (tecla >= '0' && tecla <= '9') {
    if (posBuffer == 0) {
      bufferCodigo[0] = tecla;
      bufferCodigo[1] = '-';
      posBuffer = 1;
    } else if (posBuffer == 1) {
      bufferCodigo[1] = tecla;
      posBuffer = 0; // Reinicia para la próxima entrada

      // Buscar si el código de 2 dígitos coincide con algún producto
      bool encontrado = false;
      for (uint8_t i = 0; i < TOTAL_PRODUCTOS; i++) {
        if (codigos[i][0] == bufferCodigo[0] && codigos[i][1] == bufferCodigo[1]) {
          indiceActual = i;
          encontrado = true;
          break;
        }
      }

      // Si no existe, restaurar el código del producto actual
      if (!encontrado) {
        bufferCodigo[0] = codigos[indiceActual][0];
        bufferCodigo[1] = codigos[indiceActual][1];
      }
    }
  }
}

void siguienteProducto() {
  indiceActual = (indiceActual + 1) % TOTAL_PRODUCTOS;
  bufferCodigo[0] = codigos[indiceActual][0];
  bufferCodigo[1] = codigos[indiceActual][1];
  posBuffer = 0;
}

void anteriorProducto() {
  if (indiceActual == 0) {
    indiceActual = TOTAL_PRODUCTOS - 1;
  } else {
    indiceActual--;
  }
  bufferCodigo[0] = codigos[indiceActual][0];
  bufferCodigo[1] = codigos[indiceActual][1];
  posBuffer = 0;
}

bool agregarProductoAlCarrito() {
  // Verificar si hay stock disponible para agregar otra unidad
  if (carrito[indiceActual] < stock[indiceActual]) {
    carrito[indiceActual]++;
    return true;
  }
  return false; // Stock agotado para este producto
}

const char* obtenerCodigoActual() {
  return bufferCodigo;
}

const char* obtenerNombreActual() {
  return nombres[indiceActual];
}

uint32_t obtenerPrecioActual() {
  return precios[indiceActual];
}

uint8_t obtenerStockDisponibleActual() {
  return stock[indiceActual] - carrito[indiceActual];
}

uint8_t obtenerEnCarritoActual() {
  return carrito[indiceActual];
}

uint32_t obtenerTotalCarrito() {
  uint32_t total = 0;
  for (uint8_t i = 0; i < TOTAL_PRODUCTOS; i++) {
    total += (uint32_t)carrito[i] * precios[i];
  }
  return total;
}

uint8_t obtenerCantidadTotalEnCarrito() {
  uint8_t cantidad = 0;
  for (uint8_t i = 0; i < TOTAL_PRODUCTOS; i++) {
    cantidad += carrito[i];
  }
  return cantidad;
}

void vaciarCarrito() {
  for (uint8_t i = 0; i < TOTAL_PRODUCTOS; i++) {
    carrito[i] = 0;
  }
  iniciarSeleccion();
}

void descontarStockVendido() {
  for (uint8_t i = 0; i < TOTAL_PRODUCTOS; i++) {
    if (stock[i] >= carrito[i]) {
      stock[i] -= carrito[i];
    } else {
      stock[i] = 0;
    }
    carrito[i] = 0;
  }
  iniciarSeleccion();
}
