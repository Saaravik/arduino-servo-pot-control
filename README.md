# Arduino Servo Pot Control

Proyecto PlatformIO para Arduino Uno R3. Lee un potenciómetro conectado a `A0` y mueve un servomotor conectado a `D9` entre 0° y 180°.

## Estructura

```text
.
├── platformio.ini
├── src/
│   └── main.cpp
├── .gitignore
└── AGENTS.md
```

## Conexiones

| Componente | Arduino Uno R3 |
| --- | --- |
| Potenciómetro, terminal central | `A0` |
| Potenciómetro, terminales exteriores | `5V` y `GND` |
| Señal del servo | `D9` |
| Alimentación del servo | Fuente adecuada para el servo |
| GND del servo/fuente | `GND` común con Arduino |

No alimentes servos que requieran más corriente desde el pin `5V` del Arduino. Si usas una fuente externa para el servo, une su GND con el GND del Arduino.

## Compilar y cargar

Con PlatformIO Core instalado:

```sh
pio run
pio run --target upload
pio device monitor
```

La velocidad del monitor serie configurada es 9600 baudios.
