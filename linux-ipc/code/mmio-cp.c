#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <error.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int ret;
	int sfd, dfd;
	char * smem;
	char * dmem;
	struct stat stat;
	off_t len;

	if (argc != 3)
		error(1, errno, "insufficient arguments");

	sfd = open(argv[1], O_RDONLY);
	if (sfd == -1)
		error(1, errno, "error opening src.");

	dfd = open(argv[2], O_RDWR | O_CREAT, 0666);
	if (dfd == -1)
		error(1, errno, "error opening dest.");

	ret = fstat(sfd, &stat);
	if (ret == -10)
		error(1, errno, "error stating src.");

	len = stat.st_size;

	ret = ftruncate(dfd, len);
	if (ret == -1)
		error(1, errno, "error truncating dest.");

	smem = mmap(NULL, len, PROT_READ, MAP_PRIVATE, sfd, 0);
	if (smem == MAP_FAILED)
		error(1, errno, "error mapping src.");
	
	dmem = mmap(NULL, len, PROT_WRITE, MAP_SHARED, dfd, 0);
	if (dmem == MAP_FAILED)
		error(1, errno, "error mapping dst.");

	memcpy(dmem, smem, len);

	ret = munmap(dmem, len);
	if (ret == -1)
		error(1, errno, "error unmapping dst.");

	ret = munmap(smem, len);
	if (ret == -1)
		error(1, errno, "error unmapping src.");

	close(sfd);
	close(dfd);
}
