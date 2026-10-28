# Especificación de Componentes Físicos y Hardware — DualVend

Este documento detalla la lista de componentes, especificaciones técnicas, conexionado eléctrico y requerimientos de alimentación para el sistema DualVend, diferenciando entre la fase actual de pruebas de interfaz y las fases de expansión física.

---

## 1. Componentes Actuales (Fase de Pruebas de Interfaz y Lógica)

### 1.1. Unidad de Control Principal
- **Componente:** Arduino Uno R3 (o clon compatible ATmega328P).
- **Especificaciones:**
  - Microcontrolador: ATmega328P a 16 MHz.
  - Memoria: 32 KB Flash (0.5 KB reservados para bootloader), 2 KB SRAM, 1 KB EEPROM.
  - Tensión de operación: 5V DC.
  - Alimentación recomendada: 7V a 12V DC (vía Jack DC) o 5V vía USB.

### 1.2. Módulo de Pantalla
- **Componente:** Pantalla LCD Alfanumérica 16x2 con adaptador I2C.
- **Especificaciones:**
  - Formato: 16 caracteres por línea, 2 líneas.
  - Controlador LCD: HD44780 (o compatible).
  - Mochila adaptadora I2C: Basada en expansor PCF8574 (o mochila Adafruit MCP23008).
  - Dirección I2C: `0x27` o `0x3F` en módulos físicos reales; `0x20` / `0x00` en Tinkercad.
  - Pines de conexión:
    - **VCC:** 5V de Arduino.
    - **GND:** GND de Arduino.
    - **SDA:** Pin analógico **A4** (Arduino Uno).
    - **SCL:** Pin analógico **A5** (Arduino Uno).

### 1.3. Dispositivos de Entrada (Pulsadores Frontales y Botón de Cancelación)
- **Componente:** 4 Pulsadores táctiles momentáneos (Normalmente Abiertos / Push Buttons).
- **Configuración eléctrica:** Conexión con resistencia pull-up interna (`INPUT_PULLUP`).
  - No requiere resistencias externas adicionales.
  - Un terminal del pulsador va al pin de Arduino; el terminal opuesto va directamente a GND.
  - Al pulsar, el nivel lógico pasa a `LOW` (0V).
- **Mapeo de pines actual:**
  - **P1 (Iniciar / Anterior / Agregar otro producto):** Pin Digital **2**.
  - **P2 (Siguiente producto):** Pin Digital **3**.
  - **P3 (Confirmar producto / Ir a Pagar):** Pin Digital **4**.
  - **Pext (Pulsador externo de Cancelación / Aborto general):** Pin Digital **5**.

---

## 2. Teclado Matricial 4x4 (Membrana)

Para marcación directa del código de 2 dígitos de cada producto (ej. "01", "02", "03"):

- **Componente:** Teclado matricial de membrana 4x4 (16 teclas: '0'..'9', 'A'..'D', '*', '#').
- **Conexión directa en Arduino Uno:**
  - **Filas (R1 a R4):** Pines Digitales **6, 7, 8, 9**.
  - **Columnas (C1 a C4):** Pines Digitales **10, 11, 12, 13**.
- **Equivalencias de teclas rápidas:**
  - Las teclas `'0'` a `'9'` marcan el código del producto directamente.
  - La tecla `'*'` limpia o borra el código que se estaba digitando.
  - La tecla `'#'` equivale al pulsador **P3** (confirmar).

---

## 3. Componentes para Fases Futuras (Dispensación y Pagos Físicos)

### 3.1. Subsistema de Entrega de Sólidos (Snacks)
- **Motorreductores:** Motor DC 12V con caja reductora (ej. 30 a 60 RPM, alto torque) acoplado al eje de espirales de acero continuo.
- **Microswitches de fin de carrera:** Interruptores mecánicos con palanca o rodillo para detectar el ciclo completo de 360° y detener el motor con precisión.
- **Etapa de potencia y aislamiento:** Módulo de relés de 5V optoacoplados de 4 u 8 canales, o transistores MOSFET N (ej. IRLZ44N) con diodos flyback (1N4007) para absorber picos inductivos.

### 3.2. Subsistema de Entrega de Líquidos (Bebidas)
- **Bomba Peristáltica 12V:** Bomba sanitaria con manguera de silicona grado alimenticio (evita contaminación cruzada y contacto directo con piezas mecánicas).
- **Electroválvula 12V:** Válvula solenoide normalmente cerrada para sellado instantáneo anti-goteo al finalizar el servido.
- **Caudalímetro de efecto Hall:** Sensor de flujo con turbina (ej. YF-S201 o modelo micrométrico de bajo flujo). Emite pulsos por mililitro servido. Conexión obligatoria al Pin Digital **2** (interrupción externa `INT0` de Arduino Uno).

### 3.3. Subsistema de Monedero y Tarjetas Sin Contacto
- **Lector NFC / RFID:** Módulo PN532 (vía I2C en A4/A5 o bus SPI).
- **Monedero electrónico multimoneda:** Validador programable (ej. CH-926) que reconoce monedas de \$500 y \$1.000 y envía trenes de pulsos digitales a Arduino.

---

## 4. Cuadro Resumen de Pines — Arduino Uno

| Pin Arduino Uno | Función Actual | Función Futura / Compartida |
| :--- | :--- | :--- |
| **0 (RX)** | Programación / Monitor Serie | Comunicación Serial inter-módulos |
| **1 (TX)** | Programación / Monitor Serie | Comunicación Serial inter-módulos |
| **2 (INT0)** | *Libre* | Señal de pulsos del caudalímetro (Líquidos) |
| **3** | Pulsador P1 | Alternativa: Salida control Motor 1 / PWM |
| **4** | Pulsador P2 | Alternativa: Salida control Motor 2 |
| **5** | Pulsador P3 | Alternativa: Salida control Bomba / Relé |
| **6** | Pulsador P4 | Alternativa: Salida control Electroválvula |
| **A4 (SDA)** | Bus I2C: Pantalla LCD 16x2 | Bus I2C: Teclado matricial y PN532 |
| **A5 (SCL)** | Bus I2C: Pantalla LCD 16x2 | Bus I2C: Teclado matricial y PN532 |
| **5V / GND** | Alimentación lógica de control | Común para sensores y controladores |

