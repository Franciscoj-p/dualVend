#ifndef SELECCION_H
#define SELECCION_H

#include <Arduino.h>

// Inicializa o reinicia el módulo de selección de productos
void iniciarSeleccion();

// Procesa una tecla numérica ('0'..'9') ingresada en el teclado matricial
void procesarTeclaCodigo(char tecla);

// Navegación con pulsadores P1 (Anterior) y P2 (Siguiente)
void siguienteProducto();
void anteriorProducto();

// Intenta agregar una unidad del producto actual al carrito (con P3)
// Devuelve true si se agregó con éxito, false si no hay stock disponible
bool agregarProductoAlCarrito();

// Consultas para mostrar en la pantalla LCD 16x2
const char* obtenerCodigoActual();
const char* obtenerNombreActual();
uint32_t obtenerPrecioActual();
uint8_t obtenerStockDisponibleActual();
uint8_t obtenerEnCarritoActual();

// Información del pedido / carrito completo
uint32_t obtenerTotalCarrito();
uint8_t obtenerCantidadTotalEnCarrito();
void vaciarCarrito();
void descontarStockVendido();

#endif
