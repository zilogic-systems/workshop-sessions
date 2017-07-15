from time import sleep
from gpio import *

KEY = 67
gpio_export_pin(KEY)
gpio_set_direction(KEY, "in")

print("Press Key1")
while True:
    key_value = gpio_get_value(KEY)
    if key_value == 0:
        print("Key is pressed")
        break
    sleep(0.1)

gpio_unexport_pin(KEY)
