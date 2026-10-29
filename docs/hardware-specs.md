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

### 1.3. Dispositivo de Entrada Único: Teclado Matricial 4x4 (Membrana)
Para simplificar el cableado, reducir costos y liberar pines digitales para los motores y sensores de líquidos/sólidos, **todas las entradas de usuario se realizan desde el teclado matricial 4x4**:

- **Componente:** Teclado matricial de membrana 4x4 (16 teclas).
- **Conexión en Arduino Uno:**
  - **Filas (R1 a R4):** Pines Digitales **6, 7, 8, 9**.
  - **Columnas (C1 a C4):** Pines Digitales **10, 11, 12, 13**.
- **Mapeo de Funciones del Teclado:**
  - **Dígitos `'0'` a `'9'`:** Marcación directa del código de producto ("01", "02", "03").
  - **Tecla `'*'`:** Limpiar / Corregir código tecleado.
  - **Tecla `'A'` (antes P1):** Iniciar compra / Producto anterior / Pedir otro producto.
  - **Tecla `'B'` (antes P2):** Producto siguiente.
  - **Tecla `'C'` (antes P3 / también `'#'`):** Confirmar producto / Proceder a Pagar.
  - **Tecla `'D'` (antes Pext):** Cancelar / Abortar operación en cualquier momento.

> **Ventaja de Ingeniería:** Los Pines Digitales **2, 3, 4 y 5** quedan completamente liberados para el control de relés, puente H de motores, y para las interrupciones externas (`INT0` en pin 2 y `INT1` en pin 3) del caudalímetro o monedero.

---

## 3. Componentes para Fases Futuras (Dispensación y Pagos Físicos)

### 3.1. Subsistema de Entrega de Sólidos (Snacks)
...

### 3.2. Subsistema de Entrega de Líquidos (Bebidas)
...

### 3.3. Subsistema de Monedero y Tarjetas Sin Contacto
- **Lector NFC / RFID:** ...
- **Monedero electrónico multimoneda:** ...

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

