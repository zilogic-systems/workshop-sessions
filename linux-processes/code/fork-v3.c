#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
    pid_t pid;

    pid = fork();

    if (pid == 0) {
        printf("CHILD: My PID is %d\n", getpid());
        printf("CHILD: My parent's PID is %d\n", getppid());
    } else if (pid > 0) {
        printf("PARENT: My PID is %d\n", getpid());
        printf("PARENT: My child's PID is %d\n", pid);
	sleep(1);
    } else {
        printf("ERROR: fork() failed.\n");
    }

    return 0;
}
