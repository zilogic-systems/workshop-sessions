import time

KEY = 67

export_key = open("/sys/class/gpio/export", "r+")
export_key.write(key)
export_key.close()

key_direction = open("/sys/class/gpio/gpio"+KEY+"/direction", "r+")
key_direction.write("in")
key_direction.close()

key_value = open("/sys/class/gpio/gpio"+KEY+"/value", "r+")

print "Press Key1\n"
while True:
    key_value = key_value.read()

    if key_value == 0:
        print "Key is pressed\n"
        break
    time.sleep(0.2)

key_value.close()
