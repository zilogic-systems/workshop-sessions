import time

led = 64

export_led = open("/sys/class/gpio/export", "r+")
export_led.write(led)

led_direction = open("/sys/class/gpio/gpio"+led+"/direction", "r+")
led_direction.write("out")

led_value = open("/sys/class/gpio/gpio"+led+"/value", "r+")

while True:
    led_value.write(1)
    time.sleep(1)
    led_value.write(0)

export_led.close()
led_direction.close()
led_value.close()
