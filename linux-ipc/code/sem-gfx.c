#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>

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
	int i, j;
	int ret;
	int sfd;
	struct shared * shared;
	struct stat stat;
	off_t len;
	sem_t * sem;

	sfd = open("/tmp/gfx", O_RDWR | O_CREAT, 0666);
	if (sfd == -1)
		error(1, errno, "error opening src.");

	ret = ftruncate(sfd, sizeof(*shared));
	if (ret == -1)
		error(1, errno, "error truncating src.");

	shared = mmap(NULL, sizeof(*shared), 
		      PROT_READ | PROT_WRITE, MAP_SHARED, sfd, 0);

	if (shared == MAP_FAILED)
		error(1, errno, "error mapping src.");

	ret = sem_init(&shared->sem, 1, 0);
	if (ret == -1)
		error(1, errno, "error init. semaphore");

	while (1) {
		system("clear");
		for (i = 0; i < ROWS; i++) {
			for (j = 0; j < COLS; j++) {
				putchar(shared->buf[i][j]);
			}
			putchar('\n');
		}

		sem_wait(&shared->sem);
	}

	sem_destroy(&shared->sem);

	ret = munmap(shared, len);
	if (ret == -1)
		error(1, errno, "error unmapping src.");

	close(sfd);
}
