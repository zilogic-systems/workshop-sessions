#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

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
};

int main(int argc, char *argv[])
{
	int i, j;
	int ret;
	int sfd;
	struct shared * shared;
	struct stat stat;
	off_t len;

	sfd = open("/tmp/gfx", O_RDWR | O_CREAT, 0666);
	if (sfd == -1)
		error(1, errno, "error opening src.");

	shared = mmap(NULL, sizeof(*shared),
		      PROT_WRITE, MAP_SHARED, sfd, 0);

	if (shared == MAP_FAILED)
		error(1, errno, "error mapping src.");

	while (1) {
		memcpy(shared->buf[2], "hello", 5);
		sleep(1);
		memcpy(shared->buf[2], "     ", 5);
		sleep(1);
	}
	
	ret = munmap(shared, sizeof(*shared));
	if (ret == -1)
		error(1, errno, "error unmapping src.");

	close(sfd);
}
