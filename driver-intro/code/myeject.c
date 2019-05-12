#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/cdrom.h>

int main()
{
	int fd;
	int ret;
	
	fd = open("/dev/sr0", O_RDONLY | O_NONBLOCK);
	if (fd == -1) {
		error(1, errno, "error opening CDROM device file");
	}

	ret = ioctl(fd, CDROMEJECT);
	if (ret == -1) {
		error(1, errno, "error eject CDROM");
	}

	close(fd);
}
