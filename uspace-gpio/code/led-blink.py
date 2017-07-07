import time
from gpio import GPIO

blue = GPIO("64")
blue.exportPin()
blue.dir("out")

for count in range(5): 
    blue.write("1")
    time.sleep(1)

    blue.write("0")
    time.sleep(1)

blue.unexportPin()
