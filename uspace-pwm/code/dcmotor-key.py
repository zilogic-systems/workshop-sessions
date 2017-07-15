#!/usr/bin/python
from pwm import *
from gpio import *
import time

KEY1 = 67
KEY2 = 69
MOTOR = 1

gpio_export_pin(KEY1)
gpio_export_pin(KEY2)

gpio_set_direction(KEY1, "in")
gpio_set_direction(KEY2, "in")

pwm_export_channel(MOTOR)

period = 10000000

pwm_set_period(MOTOR, period)

duty = 7000000

while True:
    key1_value = gpio_get_value(KEY1)
    key2_value = gpio_get_value(KEY2)

    if key1_value == 0:
        duty = duty - 1000000
        if duty == 4000000:
            break
        pwm_set_dutycycle(MOTOR, duty)
        pwm_enable(MOTOR)
    if key2_value == 0:
        duty = duty + 1000000
        if duty == period:
            break
        pwm_set_dutycycle(MOTOR, duty)
        pwm_enable(MOTOR)
    time.sleep(0.2)

pwm_disable(MOTOR)
pwm_unexport_channel(MOTOR)
gpio_unexport_pin(KEY1)
gpio_unexport_pin(KEY2)
