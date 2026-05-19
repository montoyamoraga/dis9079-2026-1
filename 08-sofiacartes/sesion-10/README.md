# sesion-10

lunes 18 mayo 2026

solemne 2

## Investigación

- Sensores: Dispositivo diseñado para detectar cambios en el entorno.
- Actuadores: Dispositivo que recibe una orden o señal.

Lo que queremos realizar en la solemne 2 es que desde la Raspberry pi envíe datos de un botón on/off  hacia el Arduino
y que este encienda una luz o emita algún sonido.

### Pseudocódigo
|Raspberry Pi Pico 2 W|Adafruit IO|Arduino UNO R4 wifi|
|--|--|--|
|Botón|MQTT|LED|
|ON/OFF|feed:estado|verde/rojo|

1. Presionar elbotón en la raspberry > alterna entre ON y OFF
2. La Raspberry publica "ON" "OFF" en el feed de Adafruit IO
3. El Arduino recibe el mensaje y enciende el LED correspondiente

#### Raspberry Pi Pico 2W

- Cada vez que presionas el botón, alterna entre ON y OFF (no es necesario mantenerlo)
- El LED integrado de la placa te muestra el estado actual (encendido=ON, apagado=OFF)
- Publica el texto "ON" u "OFF" en el feed estado de Adafruit IO
  
#### Arduino UNO R4 Wifi

- Recibe "ON" -> Enciende LED verde (D2), apaga el rojo
- Recibe "OFF" -> enciende LED rojo (D3), apaga el verde
- Al arrancar, ambos  LEDS parpadean 3 veces para confirmar que la conexión fue exitosa
  
