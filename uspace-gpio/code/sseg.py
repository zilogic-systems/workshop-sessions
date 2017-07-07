import time
from gpio import GPIO

enable = GPIO("63")
enable.exportPin()
enable.dir("out")

gpio_pin = ["70", "69", "67"]

for i in gpio_pin:
        pin = GPIO(i)
        pin.exportPin()
        pin.dir("out")
        pin.write("1")
