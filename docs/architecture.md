# Arquitectura Modular del Proyecto — DualVend

## 1. Organización de Carpetas

El código está estructurado en módulos para que el equipo pueda trabajar sin pisarse el código, usando el patrón del **Director de Orquesta** (`main.cpp` mínimo):

```text
src/
├── main.cpp                  --> DIRECTOR DE ORQUESTA: Setup, loop y transiciones de estados (~70 líneas)
├── tipos.h                   --> Modos de la FSM (Modo), botones físicos (Boton) y resultados
│
├── datos/                    --> LA FUENTE DE LA VERDAD (Compartida)
│   └── inventario.h / .cpp   --> Catálogo de productos, stock, carrito y tipo (sólido/líquido)
│
├── herramientas/             --> HARDWARE COMPARTIDO (Drivers base en 'main')
│   ├── pantalla.h / .cpp     --> Control del LCD 16x2 I2C (mostrar mensajes, limpiar)
│   └── entrada.h / .cpp      --> Lectura de pulsadores P1..Pext y teclado matricial 4x4
│
├── logica/
│   ├── seleccion/            --> MÓDULO DE SELECCIÓN (Encapsula su propia pantalla y navegación)
│   │   └── seleccion.h / .cpp
│   │
│   └── pagos/                --> MÓDULO DE PAGOS (Encapsula su pantalla y recepción de dinero)
│       └── pagos.h / .cpp
│
├── solidos/                  --> SUBSISTEMA DE SNACKS (Motores espirales y fines de carrera)
│   └── solidos.h / .cpp
│
└── liquidos/                 --> SUBSISTEMA DE BEBIDAS (Bomba peristáltica y electroválvula)
    └── liquidos.h / .cpp
```

---

## 2. Repartición del Trabajo por Integrantes

- **Integrantes de Selección (`src/logica/seleccion/`):**
  - Dueños absolutos de la pantalla de selección y navegación. Manejan teclado matricial y pulsadores P1/P2/P3.
  - Al confirmar el pedido, retornan `SELECCION_LISTO_IR_A_PAGOS` al director.
- **Integrantes de Pagos (`src/logica/pagos/`):**
  - Dueños de la pantalla de cobro. Reciben el total a cobrar, gestionan monedas/tarjetas/sensores.
  - Al completar el cobro, retornan `PAGO_EXITOSO` al director.
- **Grupo de Sólidos (`src/solidos/`):**
  - Dueños del hardware mecánico de entrega de snacks. Exponen `dispensarSolido()`.
- **Grupo de Líquidos (`src/liquidos/`):**
  - Dueños del hardware de dispensación de bebidas. Exponen `dispensarLiquido()`.
- **Director de Orquesta (`src/main.cpp`):**
  - Solo coordina: no contiene lógica de pantallas ni detalles internos de hardware.
