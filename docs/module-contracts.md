# Contratos de Módulos e Integración — DualVend

Este documento sirve como guía oficial para el equipo sobre cómo utilizar las herramientas compartidas (`src/herramientas/`) y cómo se comunican los módulos de **Selección**, **Pagos**, y **Dispensación (Sólidos/Líquidos)**.

---

## 1. Herramientas Compartidas (`src/herramientas/`)

Cualquier módulo (Selección, Pagos, etc.) puede incluir y utilizar estas funciones directamente.

### A. Pantalla LCD 16x2 I2C (`pantalla.h`)

Permite mostrar texto de 16 columnas x 2 filas en el display:

```cpp
#include "herramientas/pantalla.h"

// 1. Mostrar dos líneas de texto fijas (máx 16 caracteres por línea)
mostrarLineas("Total a Pagar:  ", "$3500           ");

// 2. Mostrar un mensaje temporal con pausa automática (en milisegundos)
mostrarMensajeTemporal(" Pago Exitoso!  ", " Despachando... ", 1500);

// 3. Limpiar pantalla
limpiarPantalla();
```

> **Consejo**: Siempre formatea tus cadenas con `snprintf()` o usa exactamente 16 caracteres rellenando con espacios para evitar que queden caracteres sucios de pantallas anteriores.

---

### B. Entradas: Pulsadores y Teclado (`entrada.h`)

Lee tanto los 4 pulsadores físicos como el teclado matricial 4x4:

```cpp
#include "herramientas/entrada.h"

// 1. Leer pulsadores frontales (devuelve Boton: BOTON_NINGUNO, BOTON_P1, BOTON_P2, BOTON_P3, BOTON_PEXT)
Boton b = leerPulsador();

// 2. Leer teclado matricial (devuelve char: '0'..'9', 'A'..'D', '*', '#' o '\0' si no se pulsó nada)
char tecla = leerTeclado();
```

---

## 2. Módulo de Selección de Productos (`src/logica/seleccion/`)

Maneja el catálogo ("01", "02", "03"), la disponibilidad de stock y el carrito de compras del usuario.

### Funciones disponibles (`seleccion.h`):

| Función | Tipo de Retorno | Descripción |
| :--- | :--- | :--- |
| `iniciarSeleccion()` | `void` | Reinicia el cursor de selección al primer producto. |
| `procesarTeclaCodigo(tecla)` | `void` | Procesa dígitos '0'..'9' o '*' para buscar productos por código. |
| `siguienteProducto()` | `void` | Avanza cíclicamente al siguiente producto. |
| `anteriorProducto()` | `void` | Retrocede cíclicamente al producto anterior. |
| `agregarProductoAlCarrito()` | `bool` | Agrega 1 unidad al carrito si hay stock disponible. Retorna `false` si no hay stock. |
| `obtenerCodigoActual()` | `const char*` | Devuelve el código ("01", "02", etc.) o el dígito en curso ("0-"). |
| `obtenerNombreActual()` | `const char*` | Devuelve el nombre ("Papas", "Galletas", "Gaseosa"). |
| `obtenerPrecioActual()` | `uint32_t` | Devuelve el precio individual del producto seleccionado. |
| `obtenerStockDisponibleActual()` | `uint8_t` | Devuelve el stock restante (stock físico - unidades en carrito). |
| `obtenerTotalCarrito()` | `uint32_t` | **Entrega a Pagos:** Total acumulado en pesos de todos los productos en el carrito. |
| `obtenerCantidadTotalEnCarrito()` | `uint8_t` | Cantidad total de artículos agregados en la compra. |
| `vaciarCarrito()` | `void` | Deja el carrito en 0 unidades sin afectar el stock de la máquina. |
| `descontarStockVendido()` | `void` | **Entrega a Sólidos/Líquidos:** Descuenta formalmente las unidades vendidas del stock y limpia el carrito. |

---

## 3. Contrato de Integración con el Módulo de Pagos (`src/logica/pagos/`)

### ¿Cómo recibe el control el Módulo de Pagos?
En `src/main.cpp`, cuando el usuario termina de armar su pedido y confirma con **P3**, la máquina de estados pasa a:
```cpp
modoActual = MODO_COBRO;
```

### ¿Qué datos necesita Pagos de Selección?
Pagos simplemente llama a:
```cpp
uint32_t totalACobrar = obtenerTotalCarrito();
```
Esa es la cantidad exacta de dinero que el cliente debe ingresar o acreditar.

### ¿Qué debe hacer Pagos durante `MODO_COBRO`?
Actualmente en `main.cpp` hay una simulación temporal donde presionar **P3** aprueba el cobro. 
**El integrante a cargo de Pagos debe reemplazar ese bloque simulado por su propia lógica:**

1. **Mostrar su propia interfaz en el LCD:**
   Usar `mostrarLineas()` para mostrar al usuario cuánto debe y qué saldo lleva ingresado:
   ```cpp
   // Ejemplo de lo que Pagos puede mostrar:
   char l1[17], l2[17];
   snprintf(l1, sizeof(l1), "Total: $%lu", totalACobrar);
   snprintf(l2, sizeof(l2), "Saldo: $%lu", saldoIngresado);
   mostrarLineas(l1, l2);
   ```
2. **Procesar el hardware de cobro:**
   Leer monedas, billetes, tarjeta RFID/NFC o pulsadores de prueba de pagos.
3. **Resultado del cobro:**
   - **Si el pago se completa con éxito:**
     - Mostrar mensaje de aprobación (`mostrarMensajeTemporal(" Pago Exitoso!  ", " Despachando... ", 1500);`).
     - Cambiar el estado a entrega: `modoActual = MODO_ENTREGA;`.
   - **Si el usuario presiona Cancelar (`Pext`) o hay timeout:**
     - Devolver el dinero ingresado si corresponde.
     - Llamar a `vaciarCarrito()` para cancelar el pedido.
     - Regresar a la bienvenida: `modoActual = MODO_BIENVENIDA;`.

---

## 4. Contrato con Dispensadores Físicos (`src/solidos/` y `src/liquidos/`)

Cuando `modoActual == MODO_ENTREGA`:
1. Se activan los motores correspondientes a los productos pagados.
2. Una vez completado el giro o servido de líquido, se llama a:
   ```cpp
   descontarStockVendido();
   ```
3. La máquina vuelve automáticamente a `MODO_BIENVENIDA` lista para el próximo cliente.
