#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    char buf[100];

    pipe(fd);                     // fd[0]=read end, fd[1]=write end

    printf("Enter a message: ");
    fgets(buf, sizeof(buf), stdin);   // get input from user

    write(fd[1], buf, strlen(buf));   // write user input into pipe

    char readbuf[100];
    int n = read(fd[0], readbuf, sizeof(readbuf));
    readbuf[n] = '\0';

    printf("Read back from pipe: %s", readbuf);
    return 0;
}
