import time
import os
import board
import digitalio
import wifi
import socketpool
import ssl

from adafruit_io.adafruit_io import IO_MQTT
import adafruit_minimqtt.adafruit_minimqtt as MQTT

FEED_KEY = "boton-mensaje"

# Botón en GP15 a GND
button = digitalio.DigitalInOut(board.GP15)
button.direction = digitalio.Direction.INPUT
button.pull = digitalio.Pull.UP

# LED interno Pico W
led = digitalio.DigitalInOut(board.LED)
led.direction = digitalio.Direction.OUTPUT

print("Conectando a WiFi...")
wifi.radio.connect(
    os.getenv("CIRCUITPY_WIFI_SSID"),
    os.getenv("CIRCUITPY_WIFI_PASSWORD")
)
print("WiFi conectado")

pool = socketpool.SocketPool(wifi.radio)

mqtt_client = MQTT.MQTT(
    broker="io.adafruit.com",
    username=os.getenv("ADAFRUIT_AIO_USERNAME"),
    password=os.getenv("ADAFRUIT_AIO_KEY"),
    socket_pool=pool,
    ssl_context=ssl.create_default_context(),
)

io = IO_MQTT(mqtt_client)

print("Conectando a Adafruit IO...")
io.connect()
print("Conectado a Adafruit IO")

last_button_state = True

while True:
    io.loop()

    current_state = button.value  # True = suelto, False = presionado

    if last_button_state == True and current_state == False:
        print("Botón presionado. Enviando mensaje...")

        io.publish(FEED_KEY, "mover")

        led.value = True
        time.sleep(0.2)
        led.value = False

        # debounce simple
        time.sleep(0.4)

    last_button_state = current_state
    time.sleep(0.02)