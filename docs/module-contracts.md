# Contratos de Módulos e Integración — DualVend

Este documento sirve como guía oficial para el equipo sobre cómo interactúan los módulos con `main.cpp`, qué datos comparten y qué funciones deben implementar.

---

## 1. Datos Compartidos (`src/datos/inventario.h`)

La fuente de la verdad para productos, precios, disponibilidad y compras activas.

### Estructura `Producto`:
```cpp
enum TipoProducto { TIPO_SOLIDO, TIPO_LIQUIDO };

struct Producto {
  const char* codigo;      // "01", "02", "03"
  const char* nombre;      // "Papas", "Galletas", "Gaseosa"
  uint16_t precio;         // Precio en pesos
  TipoProducto tipo;       // TIPO_SOLIDO o TIPO_LIQUIDO
  uint8_t stock;           // Stock disponible físico
  uint8_t enCarrito;       // Unidades pedidas en la compra actual
};
```

### Funciones Principales:
- `Producto* obtenerProductoPorIndice(uint8_t indice)`: Obtiene el puntero al producto para leer su nombre, precio, tipo y stock.
- `int8_t buscarIndicePorCodigo(const char* codigo)`: Busca un código tecleado (ej. `"01"`) y retorna su índice (o `-1` si no existe).
- `bool agregarAlCarrito(uint8_t indice)`: Incrementa en 1 la cantidad pedida si hay stock disponible.
- `uint32_t calcularTotalCarrito()`: Suma total en pesos a cobrar para el módulo de Pagos.
- `void vaciarCarrito()`: Restaura el carrito a 0 unidades sin alterar el stock (si el usuario cancela con Tecla `D`).
- `void descontarStockVendido()`: Descuenta definitivamente las unidades del inventario tras la entrega física exitosa.

---

## 2. Herramientas Compartidas (`src/herramientas/`)

- **Pantalla (`pantalla.h`):**
  - `mostrarLineas(linea1, linea2)`: Muestra dos líneas en el LCD 16x2.
  - `mostrarMensajeTemporal(linea1, linea2, duracionMs)`: Muestra un mensaje con pausa automática.
- **Entradas (`entrada.h`):**
  - `leerPulsador()`: Devuelve `BOTON_A`, `BOTON_B`, `BOTON_C`, `BOTON_D` o `BOTON_NINGUNO` (según las teclas del teclado 4x4).
  - `leerTeclado()`: Devuelve el caracter del teclado matricial (`'0'..'9'`, `'A'..'D'`, `'*'`, `'#'`) o `'\0'`.

---

## 3. Contrato del Módulo de Selección (`src/logica/seleccion/`)

El módulo de selección controla su propia pantalla LCD y su lógica interna de navegación.

- `void iniciarSeleccion()`: Se invoca al entrar a `MODO_SELECCION`. Prepara el cursor en el primer producto.
- `ResultadoSeleccion procesarSeleccion(Boton boton, char tecla)`:
  - Maneja la navegación con Tecla A (anterior), Tecla B (siguiente) y la marcación directa de códigos numéricos en el teclado matricial.
  - Pregunta si desea agregar otro producto (A) o ir a pagar (C).
  - Retorna `SELECCION_EN_CURSO` mientras el usuario elija productos.
  - Retorna `SELECCION_LISTO_IR_A_PAGOS` cuando el usuario confirma con C en la pantalla de carrito.

---

## 4. Contrato del Módulo de Pagos (`src/logica/pagos/`)

El integrante de Pagos es dueño absoluto de su propia pantalla y lectura de dinero:

- `void iniciarPago(uint32_t montoTotal)`:
  - Recibe el total en pesos a cobrar calculado por `calcularTotalCarrito()`.
- `ResultadoPago procesarPago(Boton boton, char tecla)`:
  - Muestra en el LCD el total y el saldo ingresado (`mostrarLineas()`).
  - Lee sensores o botones de dinero (en la simulación actual: P1 suma $500, P3 aprueba).
  - Retorna `PAGO_EN_CURSO` mientras falte dinero.
  - Retorna `PAGO_EXITOSO` cuando se complete el valor total.
  - Retorna `PAGO_CANCELADO` si el usuario decide cancelar o hay tiempo agotado.

---

## 5. Contrato de Dispensación Física (`src/solidos/` y `src/liquidos/`)

El ciclo de entrega física recorre el carrito y delega en cada subsistema según el tipo de producto:

- `bool dispensarSolido(const char* nombreProducto)`:
  - Invocado para productos marcados como `TIPO_SOLIDO`.
  - Acciona el motor de la espiral y espera confirmación de caída.
- `bool dispensarLiquido(const char* nombreProducto)`:
  - Invocado para productos marcados como `TIPO_LIQUIDO`.
  - Activa la bomba dosificadora o electroválvula por volumen/tiempo.
- Al terminar todas las dispensaciones, `main.cpp` llama a `descontarStockVendido()` y regresa a `MODO_BIENVENIDA`.
