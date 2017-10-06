from time import sleep
from gpio import *

KEY1 = 67
KEY2 = 69

RLED = 70
GLED = 65

gpio_export_pin(KEY1)
gpio_export_pin(KEY2)
gpio_export_pin(RLED)
gpio_export_pin(GLED)

gpio_set_direction(KEY1, "in")
gpio_set_direction(KEY2, "in")
gpio_set_direction(RLED, "out")
gpio_set_direction(GLED, "out")

while True:
    key1_value = gpio_get_value(KEY1)
    gpio_set_value(RLED, key1_value)

    key2_value = gpio_get_value(KEY2)
    gpio_set_value(GLED, key2_value)

    sleep(0.2)

gpio_unexport_pin(KEY1)
gpio_unexport_pin(KEY2)

gpio_unexport_pin(RLED)
gpio_unexport_pin(GLED)
