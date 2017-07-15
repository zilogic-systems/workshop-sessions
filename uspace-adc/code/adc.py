__adc_channel_path = "/sys/bus/iio/devices/iio:device2/in_voltage{}_raw"
__adc_scale_path  = "/sys/bus/iio/devices/iio:device2/in_voltage_scale"

def cat(file):
    file = open(file, "r")
    value = file.read()
    file.close()
    return value

def adc_read_value(channel):
    return cat(__adc_channel_path.format(channel))

def adc_read_voltage(channel):
    value = int(adc_read_value(channel))
    scale = float(cat(__adc_scale_path))
    return value * scale
