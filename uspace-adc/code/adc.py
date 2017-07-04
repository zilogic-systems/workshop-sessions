class ADC(object):
    def __init__(self, channel):
        self.device = "/sys/bus/iio/devices/iio:device2"
        self.channel = self.device + "/in_voltage%d_raw" % channel
        self.scale = self.device + "/in_voltage_scale"

    def path_read(self, path):
        fd = open(path, 'r')
        return fd.read().strip()

    def read_scale(self):
        return float(self.path_read(self.scale))

    def read_voltage(self):
        step = self.read_scale()
        return int(self.path_read(self.channel)) * step

    def read_value(self):
        return int(self.path_read(self.channel))
