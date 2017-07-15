from time import sleep
import serial
from gpio import *

KEY1 = 67
KEY2 = 69
LED = 64

gpio_export_pin(KEY1)
gpio_export_pin(KEY2)
gpio_export_pin(LED)

gpio_set_direction(KEY1, "in")
gpio_set_direction(KEY2, "in")
gpio_set_direction(LED, "out")

ser = serial.Serial('/dev/ttyLP1', 9600)
ser.write(b'Press any key\n')

while True:
    key1_value = gpio_get_value(KEY1)
    key2_value = gpio_get_value(KEY2)

    if key1_value == 0:
        ser.write(b'Key1 Pressed\n')
    if key2_value == 0:
        gpio_set_value(LED, 1)
        break

    sleep(0.2)
    gpio_set_value(LED, 0)

gpio_unexport_pin(KEY1)
gpio_unexport_pin(KEY2)
gpio_unexport_pin(LED)

ser.close()
