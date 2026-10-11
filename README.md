# Arduino Servo Pot Control

Proyecto PlatformIO para Arduino Uno R3. Lee un encoder rotatorio con pulsador (CLK, DT, SW, Vin y GND) y mueve un servomotor conectado a `D9` entre 0° y 180°.

El servo arranca en el centro (90°). Cada ciclo completo del encoder mueve el servo 10°: el giro horario aumenta el ángulo y el antihorario lo reduce, sin sobrepasar los límites. Al pulsar el encoder, vuelve a 90°. El código filtra los rebotes del encoder y del pulsador sin bloquear la lectura con esperas.

Si el sentido de giro queda invertido en tu módulo, cambia `encoderDirection` de `1` a `-1` en `src/main.cpp`. Algunos encoders tienen dos posiciones de clic por ciclo eléctrico; en esos modelos el movimiento ocurre cada dos clics.

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
| Encoder, CLK | `D2` |
| Encoder, DT | `D3` |
| Encoder, SW (pulsador) | `D4` |
| Encoder, Vin | `5V` |
| Encoder, GND | `GND` |
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
