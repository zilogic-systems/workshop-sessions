class PWM(object):
    def __init__(self, channel):
        self.device = "/sys/class/pwm/pwmchip16"
        self.exportpath = self.device + "/export"
        self.unexportpath = self.device + "/unexport"
        self.channel = self.device + "/pwm%d" % channel
        self.period = self.channel + "/period"
        self.duty = self.channel + "/duty_cycle"
        self.enable = self.channel + "/enable"
        self.export_path(channel)

    def fileIOpwm(self, path, data):
        fd = open(path, "wb")
        fd.write((str(data)+'\n').encode('ascii'))
        fd.close()

    def export_path(self, channel):
        self.fileIOpwm(self.exportpath, channel)

    def set_period(self, period):
        self.fileIOpwm(self.period, period)

    def set_duty(self, duty):
        self.fileIOpwm(self.duty, duty)

    def enable_pwm(self, flag):
        self.fileIOpwm(self.enable, flag)

    def unexport_path(self, channel):
        self.fileIOpwm(self.unexportpath, channel)
