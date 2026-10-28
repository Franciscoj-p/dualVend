#include "solidos.h"
#include "herramientas/pantalla.h"

void iniciarSolidos() {
  // Aquí el grupo de sólidos configurará los pines de sus relés o drivers L298N
  Serial.println(F("[SOLIDOS] Modulo de solidos inicializado"));
}

bool dispensarSolido(const char* nombreProducto) {
  Serial.print(F("[SOLIDOS] >> Accionando motor espiral para snack: "));
  Serial.println(nombreProducto);

  char linea2[17];
  snprintf(linea2, sizeof(linea2), "%-16s", nombreProducto ? nombreProducto : "Snack");
  mostrarMensajeTemporal("Entregando Snack", linea2, 1200);

  // Simulación: ciclo de motor completado
  delay(500);
  Serial.println(F("[SOLIDOS] Snack entregado con exito"));
  return true;
}
