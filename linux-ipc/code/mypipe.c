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
	int ret;

	ret = pipe(fd);
	if (ret == -1)
		error(1, errno, "error creating pipe");

	pid = fork();
	if (pid == -1)
		error(1, errno, "error forking");

	if (pid == 0) {
		printf("In child\n");

		close(fd[1]);
    		dup2(fd[0], STDIN_FILENO);
			
		execlp("sort", "sort", 0);
		error(1, errno, "error in execing");
	} else {
		printf("In parent\n");

		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);

		printf("embedded\n");
		printf("training\n");
		printf("linux\n");
      	}
}
