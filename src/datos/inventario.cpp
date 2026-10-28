#include "inventario.h"

// Definición de catálogo inicial
static const uint8_t TOTAL_PRODUCTOS = 3;

static Producto catalogo[TOTAL_PRODUCTOS] = {
  {"01", "Papas",    1000, TIPO_SOLIDO,  5, 0},
  {"02", "Galletas", 2500, TIPO_SOLIDO,  5, 0},
  {"03", "Gaseosa",  2000, TIPO_LIQUIDO, 5, 0}
};

void iniciarInventario() {
  vaciarCarrito();
}

uint8_t obtenerTotalProductos() {
  return TOTAL_PRODUCTOS;
}

Producto* obtenerProductoPorIndice(uint8_t indice) {
  if (indice < TOTAL_PRODUCTOS) {
    return &catalogo[indice];
  }
  return nullptr;
}

int8_t buscarIndicePorCodigo(const char* codigo) {
  if (codigo == nullptr) return -1;
  for (uint8_t i = 0; i < TOTAL_PRODUCTOS; i++) {
    if (catalogo[i].codigo[0] == codigo[0] && catalogo[i].codigo[1] == codigo[1]) {
      return (int8_t)i;
    }
  }
  return -1;
}

uint8_t obtenerStockDisponible(uint8_t indice) {
  if (indice < TOTAL_PRODUCTOS) {
    if (catalogo[indice].stock >= catalogo[indice].enCarrito) {
      return catalogo[indice].stock - catalogo[indice].enCarrito;
    }
  }
  return 0;
}

bool agregarAlCarrito(uint8_t indice) {
  if (indice < TOTAL_PRODUCTOS) {
    if (catalogo[indice].enCarrito < catalogo[indice].stock) {
      catalogo[indice].enCarrito++;
      return true;
    }
  }
  return false;
}

uint32_t calcularTotalCarrito() {
  uint32_t total = 0;
  for (uint8_t i = 0; i < TOTAL_PRODUCTOS; i++) {
    total += (uint32_t)catalogo[i].enCarrito * catalogo[i].precio;
  }
  return total;
}

uint8_t calcularCantidadTotalCarrito() {
  uint8_t cantidad = 0;
  for (uint8_t i = 0; i < TOTAL_PRODUCTOS; i++) {
    cantidad += catalogo[i].enCarrito;
  }
  return cantidad;
}

void vaciarCarrito() {
  for (uint8_t i = 0; i < TOTAL_PRODUCTOS; i++) {
    catalogo[i].enCarrito = 0;
  }
}

void descontarStockVendido() {
  for (uint8_t i = 0; i < TOTAL_PRODUCTOS; i++) {
    if (catalogo[i].stock >= catalogo[i].enCarrito) {
      catalogo[i].stock -= catalogo[i].enCarrito;
    } else {
      catalogo[i].stock = 0;
    }
    catalogo[i].enCarrito = 0;
  }
}
