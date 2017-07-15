from gpio import *

ON = 64

gpio_export_pin(ON)
gpio_set_direction(ON, "out")
gpio_set_value(ON, 1)

gpio_pins = ["70", "69", "67"]

for i in gpio_pin:
    gpio_export_pin(gpio_pins[i])
    gpio_set_direction(gpio_pins[i], "out")
    gpio_set_value(gpio_pins[i], 1)
