from adc import *
from pwm import *

pot = 1
bklight = 0
pwm_export_channel(bklight)
pwm_set_period(bklight, 100000)
pwm_set_dutycycle(bklight, 100000)
pwm_enable(bklight)

while True:
    volt = adc_read_value(pot)
    pwm_set_dutycycle(bklight, volt)
