#ifndef SOLIDOS_H
#define SOLIDOS_H

#include <Arduino.h>

/**
 * ==============================================================================
 * CONTRATO DEL SUBSISTEMA DE SÓLIDOS / SNACKS (src/solidos/)
 * ==============================================================================
 * A cargo del: Grupo de Sólidos
 * 
 * Responsabilidad:
 * - Configurar y controlar los motores DC / motorreductores que giran las espirales
 *   de snacks.
 * - Detectar con microswitches de fin de carrera la vuelta completa (360°).
 * - Detectar caída del producto mediante sensor óptico/infrarrojo.
 * ==============================================================================
 */

// Inicializa pines de control de motores y sensores de sólidos
void iniciarSolidos();

// Activa el mecanismo para dispensar un snack por su nombre o código
// Retorna true si la entrega fue exitosa, false si hubo atasco/falla
bool dispensarSolido(const char* nombreProducto);

#endif
