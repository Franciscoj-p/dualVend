#ifndef LIQUIDOS_H
#define LIQUIDOS_H

#include <Arduino.h>

/**
 * ==============================================================================
 * CONTRATO DEL SUBSISTEMA DE LÍQUIDOS / BEBIDAS (src/liquidos/)
 * ==============================================================================
 * A cargo del: Grupo de Líquidos
 * 
 * Responsabilidad:
 * - Configurar y activar la bomba peristáltica o electroválvula de bebidas.
 * - Medir el volumen dosificado con caudalímetro de pulsos o tiempo calibrado.
 * ==============================================================================
 */

// Inicializa pines de control de bombas y sensores de líquidos
void iniciarLiquidos();

// Activa la bomba para servir una bebida por su nombre o código
// Retorna true si el servido fue exitoso, false si hubo falta de líquido/falla
bool dispensarLiquido(const char* nombreProducto);

#endif
