#!/usr/bin/python
class PWM(object):
    def __init__(self, channel):
        self.channel = channel
        self.pwmchip_path = "/sys/class/pwm/pwmchip16/"
        self.export_path = self.pwmchip_path+"export"
        self.unexport_path = self.pwmchip_path+"unexport"
        self.pwm_path = self.pwmchip_path+"pwm"+self.channel+"/"
        self.dutycycle = self.pwm_path+"duty_cycle"
        self.period = self.pwm_path+"period"
        self.enable = self.pwm_path+"enable"
        self.polarity = self.pwm_path+"polarity"

    def export_channel(self):
        export_ch = open(self.export_path, "w")
        export_ch.write(self.channel)
        export_ch.close()

    def set_period_ns(self, period_ns):
        period = open(self.period, "w")
        period.write(period_ns)
        period.close()

    def set_dutycycle_ns(self, dutycycle_ns):
        dutycycle = open(self.dutycycle, "w")
        dutycycle.write(dutycycle_ns)
        dutycycle.close()

    def start(self):
        enable = open(self.enable, "w")
        enable.write("1")
        enable.close()

    def stop(self):
        dutycycle = open(self.dutycycle, "w")
        dutycycle.write("0")
        dutycycle.close()
        enable = open(self.enable, "w")
        enable.write("0")
        enable.close()

    def polarity(self, direction):
        polarity = open(self.polarity, "w")
        polarity.write(direction)
        polarity.close()

    def unexport_channel(self):
        dutycycle = open(self.dutycycle, "w")
        dutycycle.write("0")
        dutycycle.close()
        unexport = open(self.unexport_path, "w")
        unexport.write(self.channel)
        unexport.close()
        
