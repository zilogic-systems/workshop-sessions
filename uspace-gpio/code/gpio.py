#!/usr/bin/python
class GPIO(object):
    def __init__(self, pin):
        self.pin = pin
        self.gpio_path = "/sys/class/gpio/"
        self.export_path = self.gpio_path+"export"
        self.unexport_path = self.gpio_path+"unexport"
        self.value_path = self.gpio_path+"gpio"+self.pin+"/value"
        self.direction_path = self.gpio_path+"gpio"+self.pin+"/direction"

    def exportPin(self):
        gpio_export = open(self.export_path, "w")
        gpio_export.write(self.pin)
        gpio_export.close()

    def unexportPin(self):
        gpio_unexport = open(self.unexport_path, "w")
        gpio_unexport.write(self.pin)
        gpio_unexport.close()

    def readDir(self):
        gpio_dir = open(self.direction_path, "r")
        dir_status = gpio_dir.read()
        gpio_dir.close()

    def write(self, value):
        gpio_write = open(self.value_path, "w")
        gpio_write.write(value)
        gpio_write.close()

    def dir(self, direction):
        gpio_dir = open(self.direction_path, "w")
        gpio_dir.write(direction)
        if direction == "out":
            self.write("0")
        gpio_dir.close()

    def read(self):
        gpio_read = open(self.value_path, "r")
        value = gpio_read.read()
        gpio_read.close()
        return value
