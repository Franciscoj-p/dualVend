#include "pagos.h"
#include "herramientas/pantalla.h"

// Variables internas del estado de cobro
static uint32_t totalACobrar = 0;
static uint32_t saldoIngresado = 0;
static bool pantallaSucia = true;

void iniciarPago(uint32_t montoTotal) {
  totalACobrar = montoTotal;
  saldoIngresado = 0;
  pantallaSucia = true;
  Serial.print(F("[PAGOS] Iniciando cobro. Monto requerido: $"));
  Serial.println(totalACobrar);
}

uint32_t obtenerMontoTotalACobrar() {
  return totalACobrar;
}

uint32_t obtenerSaldoIngresado() {
  return saldoIngresado;
}

// ==============================================================================
// [PLACEHOLDER 1: PANTALLA DE PAGOS]
// Responsable: Integrante de Pagos
// Aquí puedes personalizar cómo quieres que el LCD 16x2 muestre el saldo al usuario.
// ==============================================================================
static void dibujarPantallaPagos() {
  if (!pantallaSucia) return;
  pantallaSucia = false;

  char linea1[17];
  char linea2[17];

  // Línea 1: Cobro: $3500
  snprintf(linea1, sizeof(linea1), "Cobro: $%7lu", (unsigned long)totalACobrar);

  // Línea 2: Saldo:$1000 C:Ok (o el texto que desees mostrar)
  snprintf(linea2, sizeof(linea2), "Sal:$%-4lu  C:Pagar", (unsigned long)saldoIngresado);

  mostrarLineas(linea1, linea2);
}

// ==============================================================================
// [PLACEHOLDER 2: LÓGICA DE COBRO Y ENTRADA DE DINERO]
// Responsable: Integrante de Pagos
// 
// IMPLEMENTACIÓN ACTUAL (SIMULACIÓN TEMPORAL):
// - Pulsar tecla 'A' o tecla '1' simula el ingreso de $500 pesos.
// - Pulsar tecla 'C' simula la aprobación inmediata del pago.
// 
// CÓMO REEMPLAZAR ESTE BLOQUE CUANDO TENGAS EL HARDWARE REAL:
// 1. Si usas monedero mecánico o electrónico por pulsos:
//    - Lee los pulsos (por interrupción o digitalRead) y suma al 'saldoIngresado'.
// 2. Si usas billetero o validador serial:
//    - Lee la trama serial, valida el billete y suma su denominación.
// 3. Si usas RFID / Tarjeta NFC (RC522):
//    - Lee el UID / saldo de la tarjeta, verifica si saldo >= totalACobrar y descuenta.
// 4. Cuando el pago esté listo:
//    - Muestra tu mensaje en LCD y retorna PAGO_EXITOSO.
// 5. Si el usuario cancela o se acaba el tiempo de espera:
//    - Devuelve el saldo ingresado físicamente y retorna PAGO_CANCELADO.
// ==============================================================================
ResultadoPago procesarPago(Boton boton, char tecla) {
  // Simulación con tecla 'A' o tecla '1' (+ $500)
  if (boton == BOTON_A || tecla == '1') {
    saldoIngresado += 500;
    pantallaSucia = true;
    Serial.print(F("[PAGOS] Moneda ingresada: +$500. Saldo actual: $"));
    Serial.println(saldoIngresado);
  }

  // Simulación: Si el saldo cubre el valor o si presiona C para forzar aprobación
  if (saldoIngresado >= totalACobrar || boton == BOTON_C) {
    Serial.println(F("[PAGOS] Cobro completado con exito!"));
    mostrarMensajeTemporal(" Pago Exitoso!  ", " Despachando... ", 1500);
    return PAGO_EXITOSO;
  }

  // Refrescar LCD si cambió el saldo
  dibujarPantallaPagos();

  return PAGO_EN_CURSO;
}
