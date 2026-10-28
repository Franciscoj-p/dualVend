#include "liquidos.h"
#include "herramientas/pantalla.h"

void iniciarLiquidos() {
  // Aquí el grupo de líquidos configurará los pines de su bomba y caudalímetro
  Serial.println(F("[LIQUIDOS] Modulo de liquidos inicializado"));
}

bool dispensarLiquido(const char* nombreProducto) {
  Serial.print(F("[LIQUIDOS] >> Activando bomba dosificadora para bebida: "));
  Serial.println(nombreProducto);

  char linea2[17];
  snprintf(linea2, sizeof(linea2), "%-16s", nombreProducto ? nombreProducto : "Bebida");
  mostrarMensajeTemporal("Sirviendo Bebida", linea2, 1200);

  // Simulación: llenado completado
  delay(500);
  Serial.println(F("[LIQUIDOS] Bebida servida con exito"));
  return true;
}
