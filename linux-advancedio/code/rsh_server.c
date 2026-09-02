#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>

#define MAXCMDSIZE 32

int do_process(int fd)
{
    char buff[MAXCMDSIZE];
    int n;
    pid_t childpid;

    while (1) {
        n = read(fd, buff, MAXCMDSIZE - 1);

        if (n <= 0) {
            fprintf(stderr, "client disconnected\n");
            return 0;
        }

        buff[n - 1] = '\0';

        fprintf(stderr, "received command: %s\n", buff);

        if (!strncmp("exit", buff, 4)) {
            fprintf(stderr, "exit requested\n");
            return 0;
        }

        childpid = fork();
        if (childpid < 0) {
            perror("Fork error");
            exit(-1);
        }

        if (childpid == 0) {
            char *argvec[MAXCMDSIZE / 2 + 1];
            char *tok;
            int i = 0;

            dup2(fd, 0);
            dup2(fd, 1);
            dup2(fd, 2);
            close(fd);

            tok = strtok(buff, " \t");
            while (tok != NULL) {
                argvec[i++] = tok;
                tok = strtok(NULL, " \t");
            }
            argvec[i] = NULL;

            execvp(argvec[0], argvec);
            perror("Exec error");
            exit(-1);
        }

        fprintf(stderr, "forked child pid=%d\n", childpid);
    }
}

int main(void)
{
    int fd, confd;
    struct sockaddr_in serv, cli;
    socklen_t clilen;
    int ret;
    pid_t childpid;

    signal(SIGCHLD, SIG_IGN);

    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    bzero(&serv, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    serv.sin_port = htons(5000);

    fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("Socket open error");
        exit(-1);
    }

    ret = bind(fd, (struct sockaddr *)&serv, sizeof(serv));
    if (ret < 0) {
        perror("Bind error");
        exit(-1);
    }

    ret = listen(fd, 5);
    if (ret < 0) {
        perror("listen error");
        exit(-1);
    }

    fprintf(stderr, "listening on port %d\n", ntohs(serv.sin_port));

    for (;;) {
        clilen = sizeof(cli);
        confd = accept(fd, (struct sockaddr *)&cli, &clilen);
        if (confd < 0) {
            perror("Accept error");
            exit(-1);
        }

        fprintf(stderr, "accepted connection from %s:%d\n",
                inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));

        childpid = fork();
        if (childpid < 0) {
            perror("Fork error");
            exit(-1);
        }

        if (childpid == 0) {
            close(fd);
            do_process(confd);
            close(confd);
            fprintf(stderr, "session closed\n");
            exit(0);
        } else {
            close(confd);
        }
    }

    return 0;
}
