#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/soundcard.h>
#include <error.h>
#include <errno.h>

int main()
{
	int fd;
	unsigned int volume;
	int left;
	int right;
	int ret;

	fd = open("/dev/mixer", O_RDWR);
	if (fd == -1) {
		error(1, errno, "error opening mixer");
	}

	ret = ioctl(fd, SOUND_MIXER_READ_VOLUME, &volume);
	if (ret == -1) {
		error(1, errno, "error reading volume");
	}
	
	left = volume & 0xff;
	right = (volume & 0xff00) >> 8;

	left += 20;
	right += 20;

	volume = left | (right << 8);

	ret = ioctl(fd, SOUND_MIXER_WRITE_VOLUME, &volume);
	if (ret == -1) {
		error(1, errno, "error writing volume");
	}

	return 0;
}
