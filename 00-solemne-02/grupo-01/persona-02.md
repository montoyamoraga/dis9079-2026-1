# investigaciones individuales

Tomas Catrileo / tomascatri

## Sensor
Para empezar diciendo que este sensor lo tengo en la mira desde que empezamos haciendo sintetizadores en el taller de maquinas, siempre me llamo la atencion como sin nada de cables y nada visible al ojo humano, pueda cambiar variables en el circuito que este conectado.

### Sobre lo que aprendí
El sensor infrarrojo reacciona a la radiacion de luz que esta mas alla del espectro visible humano, con eso me referia a nada visible (que bacan), existen 2 principales:
* Pasivos = Detectan el calor proveniente de los cuerpos que esten en movimiento
* Activos = Relectivos o de proximidad, tienen un led emisor y un fotodiodo (componente capaz de conerrtir la luz en corriente electrica) de receptor, Funciona de manera que el emisor dispara luz IR (Radiacion electromagnéctica que es invisible y que lo percibimos con calor) y si hay un objeto en frente la luz rebota, haciendo que el receptor lo detecte.

![IR con camara](./imagenes/camara-ir.jpg)

#### Filtrado de informacion
La luz solar y luces muy fuertes pueden afectar a la medicion de este, es por eso que son de un color oscuro, asi bloqueando la luz visible y dejando pasar solo la luz infrarroja.

![Leds infrarrojos](./imagenes/leds-ir.jpg)

Otra manera seria un filtrado por software, en donde el emisor parpadea a una frecuencia especifia y el receptor esta programado para ignorar cualquier luz que no parpade a esa velocidad exacta.

#### Visualización de datos
Los datos pueden variar de 2 formas: 
* De 0 a 1, ejemplo 1 = OBJETO DETECTADO 0 = NADA DETECTADO
* 0 a 1023, Mide la intensidad del rebote y gracias a la gran cantidad de tados de puede crear una grafica mas precisa.

#### Referente
El sistema o tecnologia LIDARR (Detección y medición de luz) Se usa mucho para escanear objetos para volverlos 3D, es un sistema que calcula cuanto tarda la luz en llegar y regresar a un obrejo y con hace para mapear lo que tenga delante.

#### Problemas del sensor
* Se vuelve loco bajo sol ya que la luz solar satura el receptor, aunque se puede soluconar ponienolo por asi decirlo algo que le sombra
* No detecta objetos negros ya que el negro absorbe todo tipo de luz en vez de reflejarla.
## Actuador

## Bibliografía
