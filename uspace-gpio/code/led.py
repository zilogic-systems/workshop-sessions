LED = 64

export_led = open("/sys/class/gpio/export", "r+")
export_led.write(led)

led_direction = open("/sys/class/gpio/gpio"+LED+"/direction", "r+")
led_direction.write("out")

led_value = open("/sys/class/gpio/gpio"+LED+"/value", "r+")
led_value.write(1)

export_led.close()
led_direction.close()
led_value.close()
