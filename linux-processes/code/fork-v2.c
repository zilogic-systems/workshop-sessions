#include <stdio.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;

    pid = fork();

    if (pid == 0) {
        printf("CHILD: I am the child process.\n");
    } else if (pid > 0) {
        printf("PARENT: I am the parent process.\n");
    } else {
        printf("ERROR: fork() failed.\n");
    }

    return 0;
}
