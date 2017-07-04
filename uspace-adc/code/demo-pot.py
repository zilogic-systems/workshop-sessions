import adc
import pwm

backlight = pwm.PWM(0)
backlight.set_period(100000)
backlight.set_duty(100000)
backlight.enable_pwm(1)
pot = adc.ADC(1)

while True:
    volt = pot.read_value()
    backlight.set_duty(volt)
