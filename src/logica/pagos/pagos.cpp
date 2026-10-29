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
// [PLACEHOLDER 1: PANTALLA DE PAGOS (LCD 20x4)]
// Responsable: Integrante de Pagos
// ==============================================================================
static void dibujarPantallaPagos() {
  if (!pantallaSucia) return;
  pantallaSucia = false;

  char linea1[21];
  char linea2[21];
  char linea3[21];
  char linea4[21];

  snprintf(linea1, sizeof(linea1), "=== ZONA DE COBRO ===");
  snprintf(linea2, sizeof(linea2), "Total:   $%7lu", (unsigned long)totalACobrar);
  snprintf(linea3, sizeof(linea3), "Ingreso: $%7lu", (unsigned long)saldoIngresado);
  snprintf(linea4, sizeof(linea4), "P1:+$500    P3:Pagar");

  mostrarLineas(linea1, linea2, linea3, linea4);
}

// ==============================================================================
// [PLACEHOLDER 2: LÓGICA DE COBRO Y ENTRADA DE DINERO]
// ==============================================================================
ResultadoPago procesarPago(Boton boton, char tecla) {
  // Simulación con pulsador P1 o tecla '1' (+ $500)
  if (boton == BOTON_P1 || tecla == '1') {
    saldoIngresado += 500;
    pantallaSucia = true;
    Serial.print(F("[PAGOS] Moneda ingresada: +$500. Saldo actual: $"));
    Serial.println(saldoIngresado);
  }

  // Simulación: Si el saldo cubre el valor o si presiona P3 para forzar aprobación
  if (saldoIngresado >= totalACobrar || boton == BOTON_P3) {
    Serial.println(F("[PAGOS] Cobro completado con exito!"));
    mostrarMensajeTemporal("   PAGO EXITOSO!    ", "  Despachando orden ", 1500, "Espere en bandeja...", "Gracias x su compra ");
    return PAGO_EXITOSO;
  }

  // Refrescar LCD si cambió el saldo
  dibujarPantallaPagos();

  return PAGO_EN_CURSO;
}
