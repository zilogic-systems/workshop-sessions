#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>

#include <stdio.h>
#include <error.h>
#include <errno.h>
#include <string.h>

enum {
	ROWS = 20,
	COLS = 20,
};

struct shared {
	char buf[ROWS][COLS];
	sem_t sem;
};

int main(int argc, char *argv[])
{
	int ret;
	int counter = 0;
	int sfd;
	struct shared * shared;
	struct stat stat;
	off_t len;

	sfd = open("/tmp/gfx", O_RDWR | O_CREAT, 0666);
	if (sfd == -1)
		error(1, errno, "error opening src.");

	shared = mmap(NULL, sizeof(*shared),
		      PROT_READ | PROT_WRITE, MAP_SHARED, sfd, 0);

	if (shared == MAP_FAILED)
		error(1, errno, "error mapping src.");

	while (1) {
		snprintf(shared->buf[2], COLS, "count: %d", counter++);		  
		sem_post(&shared->sem);
		sleep(1);
	}
	
	ret = munmap(shared, sizeof(*shared));
	if (ret == -1)
		error(1, errno, "error unmapping src.");

	close(sfd);
}
