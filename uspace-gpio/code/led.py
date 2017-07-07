LED = "64"

export_led = open("/sys/class/gpio/export", "w")
export_led.write(LED)
export_led.close()

led_direction = open("/sys/class/gpio/gpio"+LED+"/direction", "w")
led_direction.write("out")
led_direction.close()

led_value = open("/sys/class/gpio/gpio"+LED+"/value", "r+")
led_value.write("0")
led_value.close()
