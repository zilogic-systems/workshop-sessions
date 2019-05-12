#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/rtc.h>

#include <error.h>
#include <errno.h>

int main()
{
	int fd;
	struct rtc_time rtc_tm;
	int ret;

	fd = open("/dev/rtc0", O_RDONLY);
	if (fd == -1) {
		error(1, errno, "error opening RTC");
	}

	ret = ioctl(fd, RTC_RD_TIME, &rtc_tm);
	if (ret == -1) {
		error(1, errno, "error reading time");
	}

	printf("Time: %02d:%02d:%02d\n", rtc_tm.tm_hour, 
	       rtc_tm.tm_min, rtc_tm.tm_sec);
	
	return 0;
}
