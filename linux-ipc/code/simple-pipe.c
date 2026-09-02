#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <stdio.h>
#include <error.h>
#include <errno.h>

int main()
{
	int fd[2];
	pid_t pid;
	char buf[16] = "Hello\n";
	int ret;
	int i;

	ret = pipe(fd);
	if (ret == -1)
		error(1, errno, "error creating pipe");

	pid = fork();
	if (pid == -1)
		error(1, errno, "error forking");

	if (pid == 0) {
		printf("In child\n");

		close(fd[1]);
		ret = read(fd[0], buf, sizeof(buf));
		if (ret == -1)
			error(1, errno, "error reading pipe");

		for (i = 0; i < ret; i++)
			putchar(buf[i]);

	} else {
		printf("In parent\n");

		close(fd[0]);
		write(fd[1], buf, sizeof(buf));
	}
}
