#!/usr/bin/python
from pwm import *
from gpio import *
import time

MOTOR = 1

pwm_export_channel(MOTOR)

period = 10000000
pwm_set_period(MOTOR, period)
duty = 7000000
pwm_set_dutycycle(MOTOR, duty)

pwm_enable(MOTOR)
time.sleep(5)
pwm_disable(MOTOR)

pwm_unexport_channel(MOTOR)
