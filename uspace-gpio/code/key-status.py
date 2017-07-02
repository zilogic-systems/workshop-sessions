import time
import serial
from gpio import GPIO

key1 = GPIO("67")
key1.exportPin()
key1.dir("in")

key2 = GPIO("69")
key2.exportPin()
key2.dir("in")

led = GPIO("64")
led.exportPin()
led.dir("out")

ser = serial.Serial('/dev/ttyLP1', 9600)
ser.write(b'Press any key\n');

while True:
    key1_value = key1.read()
    key2_value = key2.read()

    if int(key1_value) == 0:
        ser.write(b'Key1 Pressed\n')
    if int(key2_value) == 0:
        led.write("1")
        break

    time.sleep(0.2)
    led.write("0")

key1.unexportPin()
key2.unexportPin()
led.unexportPin()
ser.close()
