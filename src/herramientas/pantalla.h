#ifndef PANTALLA_H
#define PANTALLA_H

#include <Arduino.h>

// Inicializa la pantalla LCD 16x2 I2C
void iniciarPantalla();

// Muestra dos líneas de texto en la pantalla (máximo 16 caracteres por línea)
void mostrarLineas(const char* linea1, const char* linea2);

// Limpia el contenido de la pantalla LCD
void limpiarPantalla();

// Muestra dos líneas y espera un tiempo determinado (en milisegundos)
void mostrarMensajeTemporal(const char* linea1, const char* linea2, unsigned int tiempoMs);

#endif

