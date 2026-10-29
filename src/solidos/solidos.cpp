#include "solidos.h"
#include "herramientas/pantalla.h"

// ==============================================================================
// [PLACEHOLDER 1: CONFIGURACIÓN DE PINES DE SÓLIDOS]
// Responsable: Grupo de Sólidos
// 
// CÓMO REEMPLAZAR:
// Configurar con pinMode() los pines del Arduino que controlan:
// - Driver de motorreductores (ej. puente H L298N o relés para cada espiral).
// - Entradas de microswitches de fin de carrera (normalmente INPUT_PULLUP)
//   para detectar que la espiral dio una vuelta exacta de 360°.
// - Sensor óptico / infrarrojo de caída de producto (si se implementa).
// ==============================================================================
void iniciarSolidos() {
  Serial.println(F("[SOLIDOS] Modulo de solidos inicializado (Placeholder)"));
}

// ==============================================================================
// [PLACEHOLDER 2: DISPENSACIÓN FÍSICA DE SNACK]
// Responsable: Grupo de Sólidos
// 
// IMPLEMENTACIÓN ACTUAL (SIMULACIÓN TEMPORAL):
// - Imprime mensaje por Serial y en pantalla LCD 16x2.
// - Simula un retardo de giro con delay(500) y retorna true (éxito).
// 
// CÓMO REEMPLAZAR ESTE BLOQUE CON MOTORES REALES:
// 1. Identificar cuál espiral corresponde al producto (por nombre o código).
// 2. Encender el motor correspondiente (digitalWrite(PIN_MOTOR, HIGH)).
// 3. Esperar a que el microswitch de fin de carrera pase de LOW a HIGH (giro completo).
// 4. Apagar el motor (digitalWrite(PIN_MOTOR, LOW)).
// 5. Verificar si el sensor de caída detectó el snack:
//    - Si cayó: retornar true.
//    - Si no cayó (atasco): intentar un segundo giro o retornar false para alarma.
// ==============================================================================
bool dispensarSolido(const char* nombreProducto) {
  Serial.print(F("[SOLIDOS] >> Accionando motor espiral para snack: "));
  Serial.println(nombreProducto);

  char linea2[17];
  snprintf(linea2, sizeof(linea2), "%-16s", nombreProducto ? nombreProducto : "Snack");
  mostrarMensajeTemporal("Entregando Snack", linea2, 1200);

  // Simulación temporal del tiempo de giro de la espiral
  delay(500);
  Serial.println(F("[SOLIDOS] Snack entregado con exito"));
  return true;
}
