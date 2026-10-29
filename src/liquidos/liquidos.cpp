#include "liquidos.h"
#include "herramientas/pantalla.h"

// ==============================================================================
// [PLACEHOLDER 1: CONFIGURACIÓN DE PINES DE LÍQUIDOS]
// Responsable: Grupo de Líquidos
// 
// CÓMO REEMPLAZAR:
// Configurar con pinMode() los pines del Arduino que controlan:
// - Relé o MOSFET para la bomba peristáltica / sumergible de 12V.
// - Relé para electroválvula de corte (si aplica).
// - Pin de entrada digital para pulsos de caudalímetro (ej. sensor de flujo YF-S201
//   con interrupción externa en pin 2 o 3, si están disponibles, o temporizador).
// - Sensor de nivel mínimo de líquido en el depósito.
// ==============================================================================
void iniciarLiquidos() {
  Serial.println(F("[LIQUIDOS] Modulo de liquidos inicializado (Placeholder)"));
}

// ==============================================================================
// [PLACEHOLDER 2: DISPENSACIÓN FÍSICA DE BEBIDA]
// Responsable: Grupo de Líquidos
// 
// IMPLEMENTACIÓN ACTUAL (SIMULACIÓN TEMPORAL):
// - Imprime mensaje por Serial y en pantalla LCD 16x2.
// - Simula un retardo de llenado con delay(500) y retorna true (éxito).
// 
// CÓMO REEMPLAZAR ESTE BLOQUE CON BOMBAS Y SENSORES REALES:
// 1. Encender la bomba peristáltica / válvula (digitalWrite(PIN_BOMBA, HIGH)).
// 2. Método de dosificación:
//    - Opción A (Por tiempo calibrado): Mantener encendida X segundos según el volumen del vaso.
//    - Opción B (Por caudalímetro): Contar N pulsos del sensor de flujo hasta alcanzar los mililitros deseados.
// 3. Apagar la bomba (digitalWrite(PIN_BOMBA, LOW)).
// 4. Retornar true si se dosificó completo, o false si se detectó depósito vacío.
// ==============================================================================
bool dispensarLiquido(const char* nombreProducto) {
  Serial.print(F("[LIQUIDOS] >> Activando bomba dosificadora para bebida: "));
  Serial.println(nombreProducto);

  char linea2[17];
  snprintf(linea2, sizeof(linea2), "%-16s", nombreProducto ? nombreProducto : "Bebida");
  mostrarMensajeTemporal("Sirviendo Bebida", linea2, 1200);

  // Simulación temporal del tiempo de bombeo
  delay(500);
  Serial.println(F("[LIQUIDOS] Bebida servida con exito"));
  return true;
}
