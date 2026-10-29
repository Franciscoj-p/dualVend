#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <Arduino.h>

// Tipo de dispensación física requerida
enum TipoProducto {
  TIPO_SOLIDO,   // Dispensado por motor/espiral (Grupo Sólidos)
  TIPO_LIQUIDO   // Dispensado por bomba peristáltica/válvula (Grupo Líquidos)
};

// Estructura de cada producto del sistema
struct Producto {
  const char* codigo;      // Código de 2 dígitos ("01", "02", "03")
  const char* nombre;      // Nombre ("Papas", "Galletas", "Gaseosa")
  uint16_t precio;         // Precio unitario en pesos
  TipoProducto tipo;       // Sólido o Líquido
  uint8_t stock;           // Unidades físicas disponibles en la máquina
  uint8_t enCarrito;       // Unidades apartadas en la compra actual
};

// --- FUNCIONES COMPARTIDAS DEL INVENTARIO ---

// Inicializa el catálogo y pone en cero el carrito
void iniciarInventario();

// Cantidad de productos registrados en el catálogo
uint8_t obtenerTotalProductos();

// Acceso al producto por su índice (0 a TOTAL_PRODUCTOS - 1)
Producto* obtenerProductoPorIndice(uint8_t indice);

// Busca un producto por su código de 2 dígitos. Devuelve el índice (0..N-1) o -1 si no existe
int8_t buscarIndicePorCodigo(const char* codigo);

// Agrega 1 unidad al carrito si hay stock disponible. Devuelve true si se agregó, false si no hay stock
bool agregarAlCarrito(uint8_t indice);

// Devuelve el stock disponible real (stock físico - unidades en carrito)
uint8_t obtenerStockDisponible(uint8_t indice);

// Total en pesos acumulado en el carrito de compras actual (para el módulo de Pagos)
uint32_t calcularTotalCarrito();

// Cantidad total de unidades sumadas en el carrito
uint8_t calcularCantidadTotalCarrito();

// Vacía el carrito de compras sin descontar stock físico (en caso de cancelación o aborto)
void vaciarCarrito();

// Descuenta definitivamente del stock físico las unidades vendidas y vacía el carrito
void descontarStockVendido();

#endif

