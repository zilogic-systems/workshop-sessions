from time import sleep
from gpio import *

LED = 64

gpio_export_pin(LED)
gpio_set_direction(LED, "out")

for count in range(5):
    gpio_set_value(LED, 1)
    sleep(1)

    gpio_set_value(LED, 0)
    sleep(1)

gpio_unexport_pin(LED)
