#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        printf("Child: doing some work...\n");
        sleep(2);   // Simulate work
        printf("Child: exiting now.\n");
        return 42;  // Exit status
    } else {
        // Parent process
        printf("Parent: waiting for child...\n");
        int status;
        pid_t w = wait(&status);  // Unblocks when child terminates
        printf("Parent: child %d finished, status = %d\n", w, status);
    }
    return 0;
}
