import time
from gpio import GPIO

red = GPIO("70")
red.exportPin()
red.dir("out")

green = GPIO("65")
green.exportPin()
green.dir("out")

blue = GPIO("64")
blue.exportPin()
blue.dir("out")

color_codes = ["000", "001", "010", "011", "100", "101", "110", "111"]

for color in color_codes:
    red.write(color[0])
    green.write(color[1])
    blue.write(color[2])
    time.sleep(2)

red.unexportPin()
green.unexportPin()
blue.unexportPin()
