#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#define BUFFSIZE 100

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in serv;
    struct hostent *he;

    int ret;
    char buff[BUFFSIZE];
    int nbytes;
    int written;
    int len;
    fd_set rset;

    bzero(&serv, sizeof(serv));
    serv.sin_family = AF_INET;

    if (argc == 2) {
        he = gethostbyname(argv[1]);
        if (he == NULL) {
            fprintf(stderr, "Unknown host %s\n", argv[1]);
            exit(-1);
        }
        serv.sin_addr = *((struct in_addr *)he->h_addr);
    } else {
        inet_pton(AF_INET, "127.0.0.1", &serv.sin_addr);
    }

    serv.sin_port = htons(5000);

    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Couldn't open socket");
        exit(-1);
    }

    ret = connect(sockfd, (struct sockaddr *)&serv, sizeof(serv));
    if (ret == -1) {
        perror("Cannot open a connection to the server");
        exit(-1);
    }

    FD_ZERO(&rset);

    do {
        FD_SET(0, &rset);
        FD_SET(sockfd, &rset);

        ret = select(sockfd + 1, &rset, NULL, NULL, NULL);
        if (ret == -1) {
            perror("select error");
            exit(-1);
        }

        if (FD_ISSET(0, &rset)) {
            printf("$ ");
            fflush(stdout);
            if (fgets(buff, BUFFSIZE, stdin) == NULL) {
                fprintf(stderr, "Couldn't read from stdin\n");
                continue;
            }

            len = strlen(buff);

            if (strncmp(buff, "exit", 4) == 0) {
                printf("Closing Remote Connection\n");
                close(sockfd);
                exit(0);
            }

            written = write(sockfd, buff, len);
            if (written == -1) {
                fprintf(stderr, "Couldn't write to socket\n");
            }
        }

        if (FD_ISSET(sockfd, &rset)) {
            nbytes = read(sockfd, buff, BUFFSIZE - 1);
            if (nbytes > 0) {
                buff[nbytes] = 0;
                puts(buff);
            } else if (nbytes == 0) {
                printf("Server closed connection\n");
                close(sockfd);
                exit(0);
            } else {
                perror("read error");
            }
        }
    } while (1);

    return 0;
}
