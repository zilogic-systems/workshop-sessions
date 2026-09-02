#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <linux/kd.h>
#include <linux/rtc.h>
#include <sys/ioctl.h>

void raisealert(int tone)
{
    int fd = open("/dev/console", O_WRONLY);
    if (fd == -1) {
        fprintf(stderr, "Error: can't open /dev/console\n");
        exit(-1);
    }

    struct timespec time;
    int ledstatus = 0;
    int onleds;

    time.tv_sec = 1;
    time.tv_nsec = 120000000;

    onleds = LED_SCR | LED_NUM | LED_CAP;

    ioctl(fd, KIOCSOUND, tone);
    ioctl(fd, KDGETLED, &ledstatus);
    ioctl(fd, KDSETLED, onleds);

    nanosleep(&time, NULL);

    ioctl(fd, KIOCSOUND, 0);
    ioctl(fd, KDSETLED, ledstatus);

    close(fd);
}

void setalarm(int fd, int hour, int min, int sec)
{
    int retval;
    struct rtc_time rtc_tm;
    unsigned long data;

    retval = ioctl(fd, RTC_RD_TIME, &rtc_tm);
    if (retval == -1) {
        perror("ioctl");
        exit(errno);
    }

    fprintf(stderr, "\nCurrent RTC date/time is %d-%d-%d, %02d:%02d:%02d.\n",
            rtc_tm.tm_mday, rtc_tm.tm_mon + 1, rtc_tm.tm_year + 1900,
            rtc_tm.tm_hour, rtc_tm.tm_min, rtc_tm.tm_sec);

    rtc_tm.tm_sec += sec;
    if (rtc_tm.tm_sec >= 60) {
        rtc_tm.tm_sec %= 60;
        rtc_tm.tm_min++;
    }

    rtc_tm.tm_min += min;
    if (rtc_tm.tm_min >= 60) {
        rtc_tm.tm_min %= 60;
        rtc_tm.tm_hour++;
    }

    rtc_tm.tm_hour += hour;
    if (rtc_tm.tm_hour >= 24) {
        rtc_tm.tm_hour %= 24;
    }

    retval = ioctl(fd, RTC_ALM_SET, &rtc_tm);
    if (retval == -1) {
        perror("rtc ioctl");
        exit(errno);
    }

    retval = ioctl(fd, RTC_AIE_ON, 0);
    if (retval == -1) {
        perror("rtc ioctl");
        exit(errno);
    }

    fprintf(stderr, "Waiting for alarm...");
    fflush(stderr);

    retval = read(fd, &data, sizeof(unsigned long));
    if (retval == -1) {
        perror("read");
        exit(errno);
    }

    fprintf(stderr, " okay. Alarm rang.\n");

    raisealert(500);

    retval = ioctl(fd, RTC_AIE_OFF, 0);
    if (retval == -1) {
        perror("ioctl");
        exit(errno);
    }

    close(fd);
}

int main(int argc, char *argv[])
{
    int fdrtc;
    int h = 0, m = 0, s;

    if (argc == 2) {
        s = atoi(argv[1]);
    } else {
        s = 5;
    }

    fdrtc = open("/dev/rtc", O_RDONLY);
    if (fdrtc == -1) {
        fprintf(stderr, "Error: can't open /dev/rtc\n");
        exit(-1);
    }

    setalarm(fdrtc, h, m, s);

    return 0;
}
