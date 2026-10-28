# Arquitectura Modular del Proyecto — DualVend

## 1. Organización de Carpetas

El código está estructurado en módulos para que el equipo pueda trabajar sin pisarse el código, usando funciones simples de C++ para Arduino:

```text
src/
├── main.cpp                 --> Orquestador: setup(), loop() y máquina de estados finitos (FSM)
├── tipos.h                  --> Modos de la FSM (Modo) y botones físicos (Boton)
│
├── herramientas/            --> Herramientas de hardware compartidas (disponibles en 'main')
│   ├── pantalla.h / .cpp    --> Control del LCD 16x2 I2C (mostrar mensajes, limpiar)
│   └── entrada.h / .cpp     --> Lectura de pulsadores P1..Pext y teclado matricial 4x4
│
├── logica/
│   ├── seleccion/           --> Catálogo de productos, códigos, carrito y stock (Terminado)
│   │   └── seleccion.h / .cpp
│   │
│   └── pagos/               --> Lógica de cobro, ingreso de saldo y validación (A cargo de Pagos)
│       └── pagos.h / .cpp
│
├── solidos/
│   └── solidos.h / .cpp     --> Control de motores y espirales de snacks (A cargo de Sólidos)
│
└── liquidos/
    └── liquidos.h / .cpp    --> Control de bombas y válvulas de bebidas (A cargo de Líquidos)
```

---

## 2. Repartición del Trabajo por Integrantes

- **Herramientas Compartidas (`src/herramientas/`):**
  - Base común disponible en `main` para que todos los módulos la usen sin duplicar código.
- **Módulo de Selección (`src/logica/seleccion/`):**
  - Manejo de catálogo, códigos de producto, acumulación de carrito de compras y verificación de stock.
- **Módulo de Pagos (`src/logica/pagos/`):**
  - Recibe el total a cobrar desde Selección (`obtenerTotalCarrito()`), gestiona el cobro y comunica el resultado.
- **Módulos Físicos (`src/solidos/` y `src/liquidos/`):**
  - Reciben la orden de dispensar los productos vendidos y confirman la entrega para descontar el stock.
- **Orquestador (`src/main.cpp`):**
  - Conecta la máquina de estados y las transiciones entre módulos.
