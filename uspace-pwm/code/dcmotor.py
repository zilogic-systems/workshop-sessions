#!/usr/bin/python
from pwm import PWM
from gpio import GPIO
import time


key1 = GPIO("67")
key1.exportPin()
key1.dir("in")

key2 = GPIO("69")
key2.exportPin()
key2.dir("in")

motor = PWM("1")
motor.export_channel()

period = "10000000"
motor.set_period_ns(period)
duty = 7000000

while True:    
    key1_value = key1.read()
    key2_value = key2.read()

    if int(key1_value) == 0:
        duty = duty - 1000000
        if str(duty) == "4000000":
            break
        motor.set_dutycycle_ns(str(duty))
        motor.start()
    if int(key2_value) == 0:
        duty = duty + 1000000
        if str(duty) == period:
            break
        motor.set_dutycycle_ns(str(duty))
        motor.start()
    time.sleep(0.2)

motor.stop()
motor.unexport_channel()
key1.unexportPin()
key2.unexportPin()
