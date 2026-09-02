#include <poll.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <stdio.h>
#include <errno.h>
#include <error.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define ROWS 20
#define COLS 64

void wall_init(struct pollfd * pollfds, char buf[ROWS][COLS])
{
	int i;

	struct mq_attr attr = { 0, 10, COLS };

	for (i = 0; i < ROWS; i++) {
		char name[32];
		sprintf(name, "/user%u", i);
		
		pollfds[i].fd = mq_open(name, O_RDWR | O_CREAT, 0666, &attr);
		if (pollfds[i].fd == -1)
			error(1, errno, "error opening message queue");

		pollfds[i].events = POLLIN;
	}

	system("clear");
}

void wall_cleanup(struct pollfd * pollfds)
{
	int i;

	for (i = 0; i < ROWS; i++)
		mq_close(pollfds[i].fd);
}

void trim(char * s)
{
	char * p = s;
	int l = strlen(p);
	
	while(isspace(p[l - 1])) p[--l] = 0;
	while(* p && isspace(* p)) ++p, --l;
	
	memmove(s, p, l + 1);
}

void wall_update(struct pollfd * pollfds, char buf[ROWS][COLS])
{
	int i;
	int ret;

	system("clear");
	
	for (i = 0; i < ROWS; i++) {
		if (pollfds[i].revents & POLLIN) {
			ret = mq_receive(pollfds[i].fd, buf[i], sizeof(buf[i]), NULL);
			if (ret == -1) {
				if (errno == ETIMEDOUT)
					break;
				
				error(1, errno, "error receving message");
			}
		}
	
		trim(buf[i]);
		puts(buf[i]);
	}
}

void main(int argc, char * argv[])
{
	int ret;
	int i;
	char * retp;
	struct pollfd pollfds[ROWS];
	char buf[ROWS][COLS] = {};

	wall_init(pollfds, buf);

	while (1) {
		ret = poll(pollfds, ROWS, -1);
		if (ret == -1)
			error(1, errno, "error polling fds");

		wall_update(pollfds, buf);
	}
	
	wall_cleanup(pollfds);
}
