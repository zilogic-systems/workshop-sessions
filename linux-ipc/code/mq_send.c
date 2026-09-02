#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <stdio.h>
#include <errno.h>
#include <error.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int fd;
	char buf[64];
	char * retp;
	int ret;

	if (argc != 2)
		error(1, 0, "incorrect no. of arguments");

	fd = mq_open(argv[1], O_WRONLY);
	if (fd == -1)
		error(1, errno, "error opening message queue");

	while (1) {
		printf("Enter message: ");
		retp = fgets(buf, sizeof(buf), stdin);
		if (retp == NULL)
			break;

		ret = mq_send(fd, buf, strlen(buf) + 1, 0);
		if (ret == -1)
			error(1, errno, "error sending message");
	}

	return 0;
}
