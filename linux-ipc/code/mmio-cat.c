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
	int i;
	int ret;
	int sfd;
	char * smem;
	struct stat stat;
	off_t len;

	if (argc != 2)
		error(1, errno, "insufficient arguments");

	sfd = open(argv[1], O_RDONLY);
	if (sfd == -1)
		error(1, errno, "error opening src.");

	ret = fstat(sfd, &stat);
	if (ret == -1)
		error(1, errno, "error stating src.");

	len = stat.st_size;

	smem = mmap(NULL, len, PROT_READ, MAP_SHARED, sfd, 0);
	if (smem == MAP_FAILED)
		error(1, errno, "error mapping src.");
	
	for (i = 0; i < len; i++)
		putchar(smem[i]);

	ret = munmap(smem, len);
	if (ret == -1)
		error(1, errno, "error unmapping src.");

	close(sfd);
}
