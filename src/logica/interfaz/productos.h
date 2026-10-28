#ifndef PRODUCTOS_H
#define PRODUCTOS_H

#include <Arduino.h>

// Avanza al siguiente producto (0 -> 1 -> 2 -> 0)
void siguienteProducto();

// Devuelve el nombre del producto seleccionado actualmente
const char* obtenerNombreActual();

// Devuelve el precio del producto seleccionado actualmente
uint32_t obtenerPrecioActual();

// Devuelve el índice del producto actual (0, 1 o 2)
uint8_t obtenerIndiceProducto();

#endif

