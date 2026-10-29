#ifndef PANTALLA_H
#define PANTALLA_H

#include <Arduino.h>

// Inicializa la pantalla LCD 20x4 I2C
void iniciarPantalla();

// Muestra hasta 4 líneas de texto en la pantalla (máximo 20 caracteres por línea)
// Permite llamar con 2, 3 o 4 líneas gracias a los valores por defecto.
void mostrarLineas(const char* l1, const char* l2, const char* l3 = "", const char* l4 = "");

// Limpia el contenido de la pantalla LCD
void limpiarPantalla();

// Muestra hasta 4 líneas y espera un tiempo determinado (en milisegundos)
void mostrarMensajeTemporal(const char* l1, const char* l2, unsigned int tiempoMs, const char* l3 = "", const char* l4 = "");

#endif
