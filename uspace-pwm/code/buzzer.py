import time

ch = "2"
pwm_path = "/sys/class/pwm/pwmchip16/"
export_path = pwm_path+"export"
unexport_path = pwm_path+"unexport"
period_path = pwm_path+"pwm"+ch+"/period"
duty_path = pwm_path+"pwm"+ch+"/duty_cycle"
enable_path = pwm_path+"pwm"+ch+"/enable"

export = open(export_path, "w")
export.write(ch)
export.close()

period = open(period_path, "w")
period.write("1000000")
period.close()

duty_cycle = open(duty_path, "w")
duty_cycle.write("500000")
duty_cycle.flush()

enable = open(enable_path, mode="w")
enable.write("1")
enable.flush()

time.sleep(5)

duty_cycle.write("0")
duty_cycle.close()

enable.write("0")
enable.flush()
enable.close()

unexport = open(unexport_path, "w")
unexport.write(ch)
unexport.close()
