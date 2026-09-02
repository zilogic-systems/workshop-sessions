#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <stdio.h>
#include <errno.h>
#include <error.h>

#define MSG_SIZE 64
#define MAX_MSG 10

void main(int argc, char * argv[])
{
	mqd_t mqd;
	ssize_t ret;
	char buf[MSG_SIZE];
	struct mq_attr attr = { 0, MAX_MSG, MSG_SIZE };

	mqd = mq_open("/myqueue", O_RDWR | O_CREAT, 0666, &attr);
	if (mqd == -1)
		error(1, errno, "error opening message queue");

	while (1) {
		ret = mq_receive(mqd, buf, sizeof(buf), NULL);
		if (ret == -1)
			error(1, errno, "error receving message");

		puts(buf);
	}

	ret = mq_close(mqd);
	if (ret == -1)
		error(1, errno, "error receving message");
}
