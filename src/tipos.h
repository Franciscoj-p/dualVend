#ifndef TIPOS_H
#define TIPOS_H

#include <Arduino.h>

// Estados (pantallas) de la máquina expendedora
enum Mode { 
  MODE_MENU,               // Menú principal: muestra producto y precio
  MODE_ADD_AMOUNT,         // Pantalla para recargar de a +$500
  MODE_READY_TO_READ,      // Confirmación del monto recargado
  MODE_PAY_CHOICES,        // Elegir método: Pagar con Saldo o Pago NFC
  MODE_TAP_FOR_NFC,        // Simulando acercar tarjeta NFC
  MODE_RESULT_PAY,         // Pago exitoso y muestra saldo restante
  MODE_REFUND_OR_LEAVE,    // Elegir si devolver saldo o dejarlo guardado
  MODE_NFC_SUCCESS         // Pago NFC exitoso
};

#endif

