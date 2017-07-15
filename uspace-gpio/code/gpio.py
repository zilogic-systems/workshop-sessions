from os.path import exists

__gpio_path = "/sys/class/gpio/gpio{}"
__gpio_export_path = "/sys/class/gpio/export"
__gpio_unexport_path = "/sys/class/gpio/unexport"
__gpio_direction_path = "/sys/class/gpio/gpio{}/direction"
__gpio_value_path = "/sys/class/gpio/gpio{}/value"

def cat(file):
    file = open(file, "r")
    value = file.read()
    file.close()
    return value

def echo(value, file):
    file = open(file, "w")
    file.write(value)
    file.close()

def gpio_export_pin(pin):
    if not exists(__gpio_path.format(pin)):
        echo(str(pin), __gpio_export_path)

def gpio_unexport_pin(pin):
    if exists(__gpio_path.format(pin)):
        echo(str(pin), __gpio_unexport_path)

def gpio_get_direction(pin):
    return cat(__gpio_direction_path.format(pin))

def gpio_set_direction(pin, direction):
    echo(direction, __gpio_direction_path.format(pin))

def gpio_get_value(pin):
    value = cat(__gpio_value_path.format(pin))
    return int(value)

def gpio_set_value(pin, value):
    echo(str(value), __gpio_value_path.format(pin))
