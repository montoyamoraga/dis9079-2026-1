# investigaciones individuales

nombre completo / github

## Sensor
### sensor botón / pulsador

Para esta investigación trabajé con el botón o pulsador que es uno de los sensores más simples dentro de la electrónica. Su función principal es detectar si está siendo presionado o no, por lo que solo entrega dos estados posibles: 0 o 1, apagado o encendido, abierto o cerrado. Por esto se considera un sensor digital, ya que no mide valores intermedios, sino que responde a una acción puntual.
A pesar de ser un componente muy simple, el botón es una de las formas más directas de interacción entre una persona y un sistema electrónico. Al presionarlo, el usuario entrega una instrucción clara al circuito, como encender una luz, activar un sonido, enviar un mensaje o iniciar una acción dentro de un programa. En ese sentido, **el botón funciona como un puente entre una acción física humana y una respuesta digital.** 

 <img src="./imagenes/imgboton01.png" alt="img botón 01">
 
**<ins>Funcionamiento<ins>**

El botón funciona abriendo y cerrando un circuito. Cuando no está presionado, los contactos internos están separados y cuando se presiona, estos contactos se juntan. Ese cambio es lo que después puede leer el Arduino como una señal. 

 <img src="./imagenes/imgdiagrama.png" alt="img diagrama bootón">

En Arduino esto se trabaja con los pines digitales, que leen dos estados:

**HIGH**: cuando llega una señal entre 2.6V y 5V.  
**LOW**: cuando llega una señal entre 0V y 2.5V.

 Se usan esos estados como una orden para el Arduino, si el botón está presionado puede pasar una cosa y si no está presionado, puede pasar otra.

También hay que tener cuidado con el voltaje. **Los pines de entrada no deberían recibir más de 5V, porque se puede dañar la placa**. Si se quiere usar una señal más alta, hay que bajarla antes con un **divisor de tensión**.

Para que el botón funcione bien, la señal no puede queda indefinida. Por eso se usan resistencias **pull-up o pull-down**, que ayudan a dejar claro qué valor tiene el pin cuando el botón no se está presionando. Si el pin queda indefinido Arduino puede leer cualquier cosa aunque no estemos tocando el botón.

Hay dos formas comunes de conectarlo:

**Pull-up**: cuando el botón no se presiona, el pin queda en HIGH / 5V. Al presionarlo, cambia a LOW / 0V.   
**Pull-down**: cuando el botón no se presiona, el pin queda en LOW / 0V. Al presionarlo, cambia a HIGH / 5V.

La resistencia puede ser de distintos valores, pero normalmente se usan entre 1KΩ y 10KΩ. Arduino también tiene resistencias internas que se pueden activar desde el código, pero usar una resistencia externa ayuda a entender mejor el circuito y evitar errores.
```
*  Como utilizar un botón con arduino
 *  
 *  EJEMPLO 01
 *  
 *  Ejemplo para encender y apagar un LED con un botón.
 *  
 */

// Crear variables para el manejo de los pines
int pinLED = 9;
int pinBoton = 2;

// Crear variable para estado del botón
bool boton = LOW;

void setup() {
  // Configuración de los pines de entrada y salida
  pinMode(pinLED,OUTPUT); // Salida digital para el LED
  pinMode(pinBoton,INPUT); // Entrada digital para el botón
}

void loop() {
  // Leer el estado del botón y encender o apagar el LED
  boton = digitalRead(pinBoton);

  if(boton == HIGH){            // Si el botón está pulsado
    digitalWrite(pinLED,HIGH);  // Enciende el LED
  }
  else{                         // Si no
    digitalWrite(pinLED,LOW);   // Apaga el LED
  }
}
 ```

> Código e imágenes recopiladas de: *Automatización para Todos, (2019), Utilizar Push Button con Arduino*.


**<ins>Problemas que pueden aparecer<ins>**

Uno de los problemas más comunes al trabajar con botones es el rebote. Esto pasa porque al presionar el botón, los contactos internos no se juntan de manera completamente limpia, sino que generan pequeñas vibraciones durante unos milisegundos. Aunque para nosotros sea una sola presión, la placa puede leerlo como varias pulsaciones seguidas.
Para solucionar esto se usa el **debounce**, que básicamente sirve para evitar que el sistema registre muchas lecturas falsas. Se puede hacer desde el código dejando un pequeño tiempo de espera después de detectar una presión, o también desde el circuito, agregando componentes que ayuden a estabilizar la señal.

La idea del debounce es esta: cuando Arduino detecta que el botón cambió de estado, espera unos milisegundos antes de aceptar la lectura como válida.
 
```
ejemplo: 

const int botonPin = 2;
const int ledPin = 13;

int estadoBoton = HIGH;
int ultimaLectura = HIGH;

unsigned long ultimoCambio = 0;
unsigned long tiempoDebounce = 50; // milisegundos

void setup() {
  pinMode(botonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int lectura = digitalRead(botonPin);

  // Si la lectura cambió, reiniciamos el tiempo
  if (lectura != ultimaLectura) {
    ultimoCambio = millis();
  }

  // Si ya pasó suficiente tiempo, aceptamos la lectura como real
  if ((millis() - ultimoCambio) > tiempoDebounce) {
    if (lectura != estadoBoton) {
      estadoBoton = lectura;

      // Como usamos INPUT_PULLUP, presionado es LOW
      if (estadoBoton == LOW) {
        digitalWrite(ledPin, HIGH);
      } else {
        digitalWrite(ledPin, LOW);
      }
    }
  }

  ultimaLectura = lectura;
}
```
   
 Esto significa que Arduino espera 50 milisegundos antes de aceptar el cambio del botón.
   
```
unsigned long tiempoDebounce = 50;
```

Si el botón cambia, Arduino guarda el momento en que ocurrió ese cambio. 
 
```
if ((millis() - ultimoCambio) > tiempoDebounce) {
```
Después revisa si ya pasó el tiempo suficiente. Si pasó, considera que la señal ya está estable. 

```
if ((millis() - ultimoCambio) > tiempoDebounce) {
```
Como el código usa:
 
```
pinMode(botonPin, INPUT_PULLUP);
```
el botón funciona “al revés”:

**No presionado** = HIGH  
**Presionado** = LOW

Entonces el debounce evita que una sola presión se cuente como varias.

También pueden aparecer problemas más simples, pero igual de importantes, como cables mal conectados, pines equivocados o conexiones flojas en la protoboard. Por eso, antes de pensar que el código está malo, es importante revisar bien el montaje físico.
 
**<ins>Visualización de datos<ins>**
 
Como el botón solo entrega dos estados, su visualización es bastante fácil de entender. Por ejemplo, se puede prender un LED cada vez que el botón se presiona, o mostrar en pantalla si el valor está en 0 o 1. También se puede hacer un contador de pulsaciones, donde cada presión aumente un número.
Además, se pueden definir distintos mensajes según el orden de pulsación del botón. Por ejemplo, la primera vez que se presiona puede enviar el mensaje “botón 01”, la segunda vez “botón 02” y la tercera vez “botón 03”. De esta manera, una acción simple como presionar un botón puede transformarse en un sistema numérico o secuencial, donde cada pulsación tiene un significado distinto dentro del proyecto.
Otra forma de visualizarlo es como una señal que cambia en el tiempo: cuando el botón no está presionado se mantiene en un estado, y cuando se presiona cambia al otro. Esto permite ver de manera simple cómo una acción manual se transforma en un dato que el sistema puede interpretar.

**<ins>Ejemplo de uso<ins>**
 
El botón funciona como entrada: cada vez que se presiona, envia una señal o un mensaje según el orden de pulsación. Luego, esa información puede ser recibida por otro dispositivo para activar una respuesta física. En este caso, un servo motor puede moverse a distintas posiciones dependiendo del mensaje recibido.

Por ejemplo:

Pulsación del botón	Mensaje enviado	Acción del actuador
**Primera pulsación**	botón 01	El servo se mueve a 0°   
**Segunda pulsación**	botón 02	El servo se mueve a 90°
**Tercera pulsación**	botón 03	El servo se mueve a 180°  

Así, el botón no solo activa una acción, sino que permite generar una secuencia de instrucciones. El actuador, en este caso el servo, transforma esa información digital en un movimiento físico. Esto muestra cómo una interacción simple, como presionar un botón, puede producir una respuesta visible dentro del sistema. 

### Referente: <ins>Karri Messenger 01<ins>

Como referente estoy tomando el Karri Messenger 1, también llamado Karri Classic, un dispositivo de comunicación creado por Pete Clifford, fundador de Karri. La idea del proyecto nace desde una preocupación cotidiana: cómo permitir que un niño pueda comunicarse con sus padres o cuidadores sin tener que entregarle un celular completo a una edad temprana.

Me interesa este referente porque utiliza un sensor muy simple, **el botón**, para responder a una problemática actual: la comunicación en niños. Hoy gran parte de la comunicación cotidiana ocurre a través del celular, pero entregar un celular a niños pequeños también significa abrirles acceso a redes sociales, internet, aplicaciones, notificaciones y otros espacios que pueden ser difíciles de controlar. Karri propone una solución intermedia: permite que el niño pueda comunicarse y moverse con mayor independencia, pero sin entrar completamente en la lógica del smartphone. En este caso, el botón funciona como la entrada principal del sistema, a través de una acción física simple, como presionar, el niño puede grabar o enviar un mensaje de voz. Esto me parece importante porque demuestra que no siempre se necesita una interfaz compleja para resolver una necesidad. Una interacción básica puede ser suficiente si está bien pensada y responde claramente al contexto de uso.

La lógica del botón en Karri no es solo activar algo, sino transformar una pulsación en una acción comunicativa. Al apretar el botón, el niño puede decir que llegó bien, pedir ayuda, responder un mensaje o mantenerse en contacto con su familia. Es una tecnología simple, pero con una función emocional y práctica muy clara: dar independencia sin dejar de lado el cuidado.

La salida del sistema es una respuesta comunicacional: el niño utiliza el dispositivo como un medio para comunicarse y aprender a mantenerse en contacto, mientras que los adultos pueden acompañar su recorrido desde la aplicación. Esto muestra cómo un botón puede funcionar como puente entre una acción mínima y una respuesta mucho más compleja.




## Bibliografía
https://cursos.mcielectronics.cl/2024/10/22/explicando-el-modo-arduino-input_pullup-pinmode/ 
