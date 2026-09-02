#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>

void write_buf(int fd, char *bufp, size_t nbytes, char *filename)
{
	int written;

	while (nbytes != 0) {
		written = write(fd, bufp, nbytes);
		if (written == -1)
			error(1, errno, "error writing to file %s", filename);

		if (written <= nbytes) {
			bufp += written;
			nbytes -= written;
		}
	}
}

int main(int argc, char *argv[])
{
	char *source;
	char *dest;
	int source_fd, dest_fd;

	int buf_size;
	char *buf;

	ssize_t read_len;
	struct stat stat;
	int ret;

	if (argc != 4) {
		printf("Usage: mycp <src-filename> <dest-filename> <buf-size>\n");
		exit(1);
	}

	source = argv[1];
	dest = argv[2];

	buf_size = atoi(argv[3]);
	if (buf_size == 0)
		error(1, 0, "incorrect buffer size");

	buf = malloc(buf_size);
	if (buf == NULL)
		error(1, errno, "error allocating memory");

	source_fd = open(source, O_RDONLY);
	if (source_fd == -1)
		error(1, errno, "error opening file %s", source);

	ret = fstat(source_fd, &stat);
	if (ret == -1)
		error(1, errno, "error getting mode bits of %s", source);

	dest_fd = open(dest, O_WRONLY | O_TRUNC | O_CREAT, 
		       stat.st_mode & 0777); 
	if (dest_fd == -1)
		error(1, errno, "error opening file %s", dest);

	read_len = -1;
	while (read_len != 0) {
		read_len = read(source_fd, buf, buf_size);
		if (read_len == -1)
			error(1, errno, "error reading file %s", source);
		
		if (read_len == 0)
			break;

		write_buf(dest_fd, buf, read_len, dest);
	}

	if (close(source_fd) == -1) {
		error(1, errno, "error closing file %s", source);
	}

	if (close(dest_fd) == -1) {
		error(1, errno, "error closing file %s", dest);
	}
	
	return 0;
}
