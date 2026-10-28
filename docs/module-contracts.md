# Funciones por Carpeta — DualVend

Aquí se detallan las funciones disponibles en cada módulo para que cualquiera del equipo sepa cómo usarlas desde `main.cpp`.

---

## 1. `src/logica/interfaz/`

### A. Productos (`productos.h` y `productos.cpp`)
- `void siguienteProducto()` -> Pasa al siguiente producto cíclicamente.
- `const char* obtenerNombreActual()` -> Devuelve el nombre del producto elegido.
- `uint32_t obtenerPrecioActual()` -> Devuelve el precio del producto elegido.
- `uint8_t obtenerIndiceProducto()` -> Devuelve el número de producto (0, 1 o 2).

### B. Entrada (`entrada.h` y `entrada.cpp`)
- `void configurarBotones()` -> Configura los pines con `INPUT_PULLUP`.
- `int leerBotonPresionado()` -> Devuelve `0` (P1), `1` (P2), `2` (P3), `3` (P4) o `-1` si no se presionó nada.

### C. Pantalla (`pantalla.h` y `pantalla.cpp`)
- `void iniciarPantalla()` -> Inicializa el LCD y muestra `"Iniciando..."`.
- `void dibujarPantalla(...)` -> Refresca la pantalla según el modo actual.
- `void mostrarSaldoInsuficiente()` -> Mensaje de saldo insuficiente.
- `void mostrarResultadoDevolucion(bool habiaSaldo)` -> Mensaje de devolución.
- `void mostrarSaldoAcumulado()` -> Mensaje de saldo guardado.
- `void mostrarGracias()` -> Mensaje de despedida.

---

## 2. `src/logica/pagos/` (`pagos.h` y `pagos.cpp`)

- `void reiniciarRecarga()` -> Pone en 0 el monto a recargar.
- `void sumar500()` -> Suma +$500 al monto (hasta $20.000).
- `bool intentarCobrar(uint32_t precio)` -> Descuenta el saldo si alcanza (retorna `true`) o lo rechaza (retorna `false`).
- `bool devolverSaldo()` -> Restablece el saldo a 0 y retorna `true` si devolvió dinero.
- `uint32_t obtenerMontoRecarga()` -> Consulta el monto de recarga en curso.
- `uint32_t obtenerSaldoTarjeta()` -> Consulta el saldo restante acumulado.

---

## 3. `src/solidos/` (`solidos.h` y `solidos.cpp`)

- `void iniciarSolidos()` -> Configuración de pines de motores y microswitches.
- `bool dispensarSolido(uint8_t producto)` -> Accionamiento de espiral para snacks.

---

## 4. `src/liquidos/` (`liquidos.h` y `liquidos.cpp`)

- `void iniciarLiquidos()` -> Configuración de pines de bomba y caudalímetro.
- `bool dispensarLiquido(uint8_t producto)` -> Dosificación de bebidas.
