#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <error.h>

void child()
{
	sleep(20);
}

void handler(int signum)
{
	return;
}

void parent()
{
	int stat;
	pid_t pid;

	signal(SIGALRM, handler);
	siginterrupt(SIGALRM, 0);
	alarm(2);

	pid = wait(&stat);
	if (pid == -1)
		error(1, errno, "error during wait");
}

int main()
{
	pid_t cpid;

	cpid = fork();
	switch (cpid) {
	case 0:
		child();
		break;
	case -1:
		error(1, errno, "error forking child");
	default:
		parent();
		break;
	}

	return 0;
}
