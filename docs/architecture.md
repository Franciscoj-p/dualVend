# Arquitectura Modular del Proyecto — DualVend

## 1. Organización de Carpetas

El código está estructurado en carpetas según las áreas de trabajo del equipo, manteniendo las funciones simples de C++ para Arduino:

```text
src/
├── main.cpp                 --> El cerebro: setup(), loop() y coordinación de botones
├── tipos.h                  --> Modos/pantallas de la máquina (enum Mode)
│
├── logica/
│   ├── interfaz/
│   │   ├── pantalla.h / .cpp   --> Control y mensajes de la pantalla LCD 16x2 I2C
│   │   ├── entrada.h / .cpp    --> Lectura de los 4 botones (con antirrebote)
│   │   └── productos.h / .cpp  --> Nombres, precios y selección de productos
│   │
│   └── pagos/
│       └── pagos.h / .cpp      --> Saldo, recargas de +$500, cobro y devolución
│
├── solidos/
│   └── solidos.h / .cpp        --> Motores y espirales para entrega de snacks
│
└── liquidos/
    └── liquidos.h / .cpp       --> Bomba peristáltica y electroválvula para bebidas
```

---

## 2. Repartición del Trabajo por Integrantes

- **Persona 1 (Interfaz y Selección):**
  - Trabaja en `src/logica/interfaz/` (`pantalla.cpp`, `entrada.cpp`, `productos.cpp`).
- **Persona 2 (Dinero y Pagos):**
  - Trabaja en `src/logica/pagos/` (`pagos.cpp`).
- **Grupo de Sólidos:**
  - Trabaja en `src/solidos/` (`solidos.cpp`).
- **Grupo de Líquidos:**
  - Trabaja en `src/liquidos/` (`liquidos.cpp`).
- **Integración general:**
  - Se orquesta desde `src/main.cpp`.
