// instalar bibliotecas
// WiFiS3
// PubSubClient
// Servo

#include <WiFiS3.h>
#include <PubSubClient.h>
#include <Servo.h>


// -------------------------
// datos que debes modificar
// -------------------------

// nombre de tu red wifi
const char* WIFI_SSID = "TU_WIFI";

// contraseña de tu red wifi
const char* WIFI_PASS = "TU_PASSWORD";

// nombre de usuario de adafruit io
// ejemplo: mateo123
const char* AIO_USERNAME = "TU_USUARIO_ADAFRUIT_IO";

// clave aio key de adafruit io
// se obtiene en:
// adafruit io > settings > view aio key
const char* AIO_KEY = "TU_AIO_KEY";

// nombre del feed creado en adafruit io
// debe ser exactamente igual al usado en la pico
const char* FEED_KEY = "boton-mensaje";


// -------------------------
// configuración mqtt
// -------------------------

// servidor mqtt de adafruit io
const char* MQTT_SERVER = "io.adafruit.com";

// puerto mqtt estándar
const int MQTT_PORT = 1883;

// aquí se almacenará automáticamente
// la ruta completa del feed
char mqttTopic[100];


// -------------------------
// creación de objetos
// -------------------------

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

Servo servoMotor;


// -------------------------
// configuración de pines
// -------------------------

// pin donde conectar la señal del servo
const int SERVO_PIN = 9;

// led interno del arduino
const int LED_PIN = LED_BUILTIN;


// -------------------------
// función que mueve el servo
// se ejecutará cuando llegue
// el mensaje desde adafruit io
// -------------------------

void moverServo() {

  // encender led para mostrar actividad
  digitalWrite(LED_PIN, HIGH);

  // mover servo hacia un lado
  servoMotor.write(30);
  delay(400);

  // mover servo hacia el otro lado
  servoMotor.write(150);
  delay(400);

  // regresar al centro
  servoMotor.write(90);
  delay(400);

  // apagar led
  digitalWrite(LED_PIN, LOW);
}


// -------------------------
// esta función se ejecuta
// automáticamente cuando
// llega un mensaje mqtt
// -------------------------

void callback(char* topic, byte* payload, unsigned int length) {

  // variable donde reconstruiremos
  // el mensaje recibido
  String mensaje = "";

  // convertir arreglo de bytes a texto
  for (unsigned int i = 0; i < length; i++) {
    mensaje += (char)payload[i];
  }

  // mostrar información recibida
  Serial.print("mensaje recibido en: ");
  Serial.println(topic);

  Serial.print("contenido: ");
  Serial.println(mensaje);


  // si el mensaje recibido es "mover"
  // activar movimiento

  if (mensaje == "mover") {
    moverServo();
  }
}


// -------------------------
// conectar a wifi
// -------------------------

void conectarWiFi() {

  Serial.print("conectando a wifi");

  // intentar conexión hasta lograrlo
  while (WiFi.begin(WIFI_SSID, WIFI_PASS) != WL_CONNECTED) {

    Serial.print(".");

    // esperar antes de reintentar
    delay(3000);
  }

  Serial.println();
  Serial.println("wifi conectado");

  // mostrar ip obtenida
  Serial.print("ip: ");
  Serial.println(WiFi.localIP());
}


// -------------------------
// conectar a adafruit io
// mediante mqtt
// -------------------------

void conectarMQTT() {

  while (!mqttClient.connected()) {

    Serial.print("conectando a mqtt...");

    // generar id aleatorio
    // evita conflictos si existen
    // varios dispositivos conectados

    String clientId = "arduino-r4-";
    clientId += String(random(0xffff), HEX);


    // conectar usando usuario y clave aio

    if (mqttClient.connect(
      clientId.c_str(),
      AIO_USERNAME,
      AIO_KEY
    )) {

      Serial.println("conectado");


      // construir topic:
      // usuario/feeds/feed

      snprintf(
        mqttTopic,
        sizeof(mqttTopic),
        "%s/feeds/%s",
        AIO_USERNAME,
        FEED_KEY
      );


      // suscribirse para escuchar mensajes

      mqttClient.subscribe(mqttTopic);

      Serial.print("escuchando: ");
      Serial.println(mqttTopic);

    }

    else {

      Serial.println("error");
      Serial.print("codigo: ");
      Serial.println(mqttClient.state());

      // esperar antes de intentar nuevamente
      delay(5000);
    }
  }
}


// -------------------------
// setup
// se ejecuta una sola vez
// -------------------------

void setup() {

  // iniciar monitor serial
  Serial.begin(115200);

  delay(1000);

  // configurar led interno
  pinMode(LED_PIN, OUTPUT);


  // inicializar servo
  servoMotor.attach(SERVO_PIN);

  // posición inicial
  servoMotor.write(90);


  // conectar a internet
  conectarWiFi();


  // configurar mqtt

  mqttClient.setServer(
    MQTT_SERVER,
    MQTT_PORT
  );

  mqttClient.setCallback(callback);

}


// -------------------------
// loop principal
// se ejecuta continuamente
// -------------------------

void loop() {

  // si mqtt se desconecta
  // volver a conectarse

  if (!mqttClient.connected()) {
    conectarMQTT();
  }

  // revisar mensajes nuevos
  mqttClient.loop();

}