from gpio import *

KEY = 67
gpio_export_pin(KEY)
gpio_set_direction(KEY, "in")

print("Press Key1")
while True:
    key_state = gpio_get_value(KEY)

    if key_state == 0:
        print("Key is pressed\n")
        break

gpio_unexport_pin(KEY)
