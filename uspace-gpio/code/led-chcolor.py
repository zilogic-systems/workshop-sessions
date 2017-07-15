import time
from gpio import *

RED_LED = 70
GREEN_LED = 65
BLUE_LED = 64

gpio_export_pin(RED_LED)
gpio_export_pin(GREEN_LED)
gpio_export_pin(BLUE_LED)

gpio_set_direction(RED_LED, "out")
gpio_set_direction(GREEN_LED, "out")
gpio_set_direction(BLUE_LED, "out")

color_codes = ["000", "001", "010", "011", "100", "101", "110", "111"]

for color in color_codes:
    gpio_set_value(RED_LED, int(color[0]))
    gpio_set_value(GREEN_LED, int(color[1]))
    gpio_set_value(BLUE_LED, int(color[2]))
    time.sleep(2)

gpio_unexport_pin(RED_LED)
gpio_unexport_pin(GREEN_LED)
gpio_unexport_pin(BLUE_LED)
