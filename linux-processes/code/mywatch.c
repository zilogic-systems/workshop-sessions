#include <stdio.h>
#include <error.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int ret;
	if (argc < 2) {
		puts("Usage: mywatch <cmd>");
		return 1;
	}

	while (1) {
		system("clear");

		ret = fork();
		if (ret == -1)
			error(1, errno, "error creating sub-process");

		if (ret == 0) {
			/* Child Process */
			execvp(argv[1], &argv[1]);
			error(1, errno, "error executing %s", argv[1]);
		} else {
			/* Parent Process */
			wait(NULL);
		}

		sleep(2);
	}
}
