#!/usr/bin/python
from pwm import *
import time

MOTOR = 1

pwm_export_channel(MOTOR)

period_ns = 10000000
pwm_set_period(MOTOR, period_ns)

while True:
    for duty in [30, 100]:
        duty_ns = int(period_ns * duty / 100)
        pwm_set_dutycycle(MOTOR, duty_ns)

        pwm_enable(MOTOR)
        time.sleep(5)
        pwm_disable(MOTOR)

pwm_unexport_channel(MOTOR)
