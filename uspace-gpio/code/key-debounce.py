import time
from gpio import GPIO

key = GPIO("67")
key.exportPin()
key.dir("in")

print("Press Key1")
while True:
    key_state = key.read()

    if int(key_state) == 0:
        print("Key is pressed\n")
        break
    time.sleep(0.1)

key.unexportPin()
