#include "pagos.h"
#include "herramientas/pantalla.h"

// Variables internas del estado de pago
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

static void dibujarPantallaPagos() {
  if (!pantallaSucia) return;
  pantallaSucia = false;

  char linea1[17];
  char linea2[17];

  // Línea 1: Cobro: $3500
  snprintf(linea1, sizeof(linea1), "Cobro: $%7lu", (unsigned long)totalACobrar);

  // Línea 2: Saldo:$1000 P3:Ok (o guía de simulación)
  snprintf(linea2, sizeof(linea2), "Sal:$%-4lu  P3:Ok", (unsigned long)saldoIngresado);

  mostrarLineas(linea1, linea2);
}

ResultadoPago procesarPago(Boton boton, char tecla) {
  // ----------------------------------------------------------------------------
  // SIMULACIÓN DE PAGO TEMPORAL (Para ser reemplazada por el integrante de Pagos)
  // ----------------------------------------------------------------------------
  // - Pulsar P1 o la tecla '1' simula el ingreso de $500 pesos.
  // - Pulsar P3 aprueba el pago inmediatamente si ya cubre el costo (o forzado para prueba).
  // ----------------------------------------------------------------------------

  if (boton == BOTON_P1 || tecla == '1') {
    saldoIngresado += 500;
    pantallaSucia = true;
    Serial.print(F("[PAGOS] Moneda ingresada: +$500. Saldo actual: $"));
    Serial.println(saldoIngresado);
  }

  // Si el saldo ingresado ya cubre el total, o si presiona P3 para simular aprobación
  if (saldoIngresado >= totalACobrar || boton == BOTON_P3) {
    Serial.println(F("[PAGOS] Cobro cubierto exitosamente!"));
    mostrarMensajeTemporal(" Pago Exitoso!  ", " Despachando... ", 1500);
    return PAGO_EXITOSO;
  }

  // Refrescar LCD si cambió el saldo
  dibujarPantallaPagos();

  return PAGO_EN_CURSO;
}
