from os.path import exists

__pwm_path = "/sys/class/pwm/pwmchip16/pwm{}"
__pwm_export_path = "/sys/class/pwm/pwmchip16//export"
__pwm_unexport_path = "/sys/class/pwm/pwmchip16/unexport"
__pwm_period_path = "/sys/class/pwm/pwmchip16/pwm{}/period"
__pwm_dutycycle_path = "/sys/class/pwm/pwmchip16/pwm{}/duty_cycle"
__pwm_enable_path = "/sys/class/pwm/pwmchip16/pwm{}/enable"

def cat(file):
    file = open(file, "r")
    value = file.read()
    file.close()
    return value

def echo(value, file):
    file = open(file, "w")
    file.write(value)
    file.close()

def pwm_export_channel(channel):
    if not exists(__pwm_path.format(channel)):
        echo(str(channel), __pwm_export_path)

def pwm_unexport_channel(channel):
    if exists(__pwm_path.format(channel)):
        echo(str(channel), __pwm_unexport_path)

def pwm_set_period(channel, period):
    echo(str(period), __pwm_period_path.format(channel))

def pwm_set_dutycycle(channel, dutycycle):
    echo(str(dutycycle), __pwm_dutycycle_path.format(channel))

def pwm_enable(channel):
    echo(str(1), __pwm_enable_path.format(channel))

def pwm_disable(channel):
    echo(str(0), __pwm_enable_path.format(channel))
