#include "productos.h"

// Lista de precios y nombres
const uint16_t prices[] = {1000, 2500, 2000};
const char* productNames[] = {"Snack 1", "Snack 2", "Bebida 1"};
uint8_t selectedProduct = 0;

void siguienteProducto() {
  selectedProduct = (selectedProduct + 1) % 3;
}

const char* obtenerNombreActual() {
  return productNames[selectedProduct];
}

uint32_t obtenerPrecioActual() {
  return prices[selectedProduct];
}

uint8_t obtenerIndiceProducto() {
  return selectedProduct;
}

