#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>

int main()
{
	int fd;
	char buf[3];
	int ret;

	fd = open("/dev/input/mice", O_RDONLY);
	if (fd == -1) {
		error(1, errno, "error opening mouse device");
	}

	while (1) {
		ret = read(fd, buf, sizeof(buf));
		if (ret == -1) {
			error(1, errno, "error reading mouse device");
		}

		printf("%d\n", ret);

		if (buf[0] & 0x01) {
			printf("Left Button Clicked\n");
		} else if (buf[0] & 0x02) {
			printf("Right Button Clicked\n");
		} else if (buf[0] & 0x04) {
			printf("Middle Button Clicked\n");
		}
	}
}
