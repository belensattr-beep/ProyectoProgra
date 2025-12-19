# Sistema de Cobro de Pasajes con Tarjetas NFC basado en ESP32

##  Descripción del proyecto
Este proyecto consiste en el desarrollo de un sistema de cobro y recarga de pasajes utilizando tarjetas NFC, basado en un microcontrolador ESP32.  
El sistema permite identificar tarjetas mediante su UID, gestionar distintos tipos de usuarios (común, estudiante y adulto mayor), realizar recargas, efectuar cobros automáticos y almacenar la información en una memoria SD.

El proyecto fue desarrollado con fines académicos dentro del área de Ingeniería Mecatrónica, integrando hardware, programación orientada a objetos y comunicación NFC.

---

##  Objetivo general
Desarrollar un sistema automatizado de cobro y recarga de pasajes mediante tecnología NFC, utilizando un ESP32, que permita la identificación de tarjetas, la gestión de saldos y el registro de operaciones.

---

##  Objetivos específicos
- Implementar la lectura de tarjetas NFC mediante el módulo PN532.
- Diseñar un sistema de gestión de usuarios con distintos tipos de tarjeta.
- Desarrollar un modo kiosco para la recarga de saldo.
- Implementar un modo de cobro automático de pasajes.
- Registrar las operaciones en una tarjeta SD.
- Mostrar información al usuario mediante una pantalla LCD.
- Aplicar programación orientada a objetos en el desarrollo del software.

---

##  Marco teórico (resumen)
El sistema se basa en la tecnología **NFC (Near Field Communication)**, que permite la comunicación inalámbrica de corto alcance entre dispositivos compatibles.  
El ESP32 actúa como unidad central de procesamiento, gestionando la lectura del UID de las tarjetas, el control de periféricos y el almacenamiento de datos.

Se emplean componentes electrónicos pasivos y activos como resistencias, capacitores y transistores para el correcto funcionamiento de los módulos, además de buses de comunicación como I2C y SPI.

---

##  Componentes utilizados

### Hardware
- ESP32
- Módulo NFC PN532
- Pantalla LCD I2C 16x2
- Módulo lector de tarjeta SD
- Buzzer
- Teclado matricial
- Transistor NPN 2N2222A
- Resistencia de 1 kΩ
- Capacitor electrolítico de 10 µF
- Fuente de alimentación
- Cables y protoboard

### Software
- Arduino IDE
- Librerías:
  - Adafruit PN532
  - LiquidCrystal I2C
  - SD
  - Wire
  - SPI
  - RTClib

---

##  Arquitectura del sistema
El sistema se divide en dos modos de funcionamiento:

- **Modo Kiosco**: permite crear tarjetas nuevas y recargar saldo.
- **Modo Cobro**: descuenta automáticamente el saldo según el tipo de tarjeta.

Ambos modos comparten la misma base de datos almacenada en la tarjeta SD.

---

##  Estructura del proyecto
/
├── src/
│ ├── Config.h
│ ├── Hardware.h / Hardware.cpp
│ ├── Tarjeta.h / Tarjeta.cpp
│ ├── Kiosko.h / Kiosko.cpp
│ ├── Cobro.h / Cobro.cpp
│ └── main.ino
├── README.md
└── docs/
└── Diagramas y documentación

---
Conexiones del Proyecto – Sistema de Cobro NFC (ESP32)
Configuración final de conexiones según el hardware utilizado:
- ESP32 Dev Module
- PN532 en modo I2C
- RTC DS3231 en I2C
- LCD 16x2 en I2C
- Módulo SD por SPI
- Keypad 4x4
- Buzzer de 3 pines

1. Bus I2C (Compartido)
Todos los siguientes módulos comparten el bus I2C:
SDA → GPIO 21
SCL → GPIO 22

PN532 (modo I2C):
- SDA → GPIO 21
- SCL → GPIO 22
- VCC → 5V
- GND → GND

RTC DS3231:
- SDA → GPIO 21
- SCL → GPIO 22
- VCC → 5V
- GND → GND

LCD I2C:
- SDA → GPIO 21
- SCL → GPIO 22
- VCC → 5V
- GND → GND

2. Bus SPI (Módulo SD)
El módulo SD utiliza el bus SPI:
- SCK → GPIO 18
- MOSI → GPIO 23
- MISO (MOSO) → GPIO 19
- CS → GPIO 5
- VCC → 5V
- GND → GND

3. Keypad 4x4
Conexión del teclado matricial 4x4:

Filas:
- F1 → GPIO 4
- F2 → GPIO 12
- F3 → GPIO 13
- F4 → GPIO 14

Columnas:
- C1 → GPIO 16
- C2 → GPIO 17
- C3 → GPIO 25
- C4 → GPIO 26

Nota: El keypad no utiliza VCC ni GND.
4. Buzzer (3 pines)
- GND → GND
- VCC → 5V
- I/O → GPIO 32

5. Masa común
Todos los módulos deben compartir la misma conexión GND con el ESP32.
Sin masa común el sistema no funcionará correctamente.
6. Orden recomendado de conexión y prueba
1. ESP32 solo
2. I2C Scanner (LCD, RTC, PN532)
3. PN532 I2C
4. RTC
5. LCD I2C
6. SD SPI
7. Keypad
8. Buzzer
9. Integración completa del sistema


##  Pruebas de funcionamiento
- Lectura correcta del UID de tarjetas NFC.
- Creación y recarga de tarjetas nuevas.
- Descuento automático de saldo en modo cobro.
- Registro correcto de operaciones en la SD.
- Visualización de mensajes en la pantalla LCD.
- Señalización sonora mediante buzzer.

---

##  Resultados
El sistema funcionó de manera estable durante las pruebas, permitiendo simular un sistema real de cobro de pasajes, cumpliendo con los objetivos planteados y demostrando la correcta integración entre hardware y software.

---

##  Conclusiones
El proyecto permitió aplicar conocimientos de electrónica, programación y sistemas embebidos, logrando un sistema funcional y escalable.  
La tecnología NFC demostró ser adecuada para aplicaciones de identificación y pago, y el uso del ESP32 facilitó la integración de múltiples periféricos.

---

##  Referencias
- Datasheet ESP32 – Espressif Systems  
- Datasheet PN532 – NXP Semiconductors  
- Arduino Documentation  
- Adafruit PN532 Library Documentation  
- RTClib Documentation  

---

##  Autores
- Andrei Nagel Zelaya  
- Maria Belén Satt Rivera  

Ingeniería Mecatrónica
