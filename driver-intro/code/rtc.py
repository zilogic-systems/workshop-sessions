import struct
import fcntl
import ioctl

# struct rtc_time {
# 	int tm_sec;
# 	int tm_min;
# 	int tm_hour;
# 	int tm_mday;
# 	int tm_mon;
# 	int tm_year;
# 	int tm_wday;
# 	int tm_yday;
# 	int tm_isdst;
# };

fmt = "iiiiiiiii"
time = bytearray(struct.calcsize(fmt))

fp = open("/dev/rtc0")
fcntl.ioctl(fp, ioctl.RTC_RD_TIME, time)
sec, min, hour, mday, mon, year, wday, yday, isdst = struct.unpack(fmt, time)
fp.close()

print("Time: {0:02}:{1:02}:{2:02}".format(hour, min, sec))
print("Date: {0}/{1}/{2}".format(mday, mon+1, year+1900))
