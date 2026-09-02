/*
 * download.c
 *
 * Simple HTTP file downloader.
 *
 * Usage:
 *      ./download <server-ip> <port> <filename>
 *
 * Example:
 *      ./download 127.0.0.1 8080 logo.png
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUF_SIZE 4096

int main(int argc, char *argv[])
{
    int sockfd;
    int port;
    struct sockaddr_in server_addr;
    FILE *sock_fp;
    FILE *file_fp;
    char http_req[1024];
    char line[1024];
    char buffer[BUF_SIZE];
    size_t n;

    if (argc != 4) {
        fprintf(stderr,
            "Usage: %s <server-ip> <port> <filename>\n",
            argv[0]);
        return 1;
    }

    port = atoi(argv[2]);

    /* Create socket */

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }

    /* Server address */

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0) {
        perror("inet_pton");
        close(sockfd);
        return 1;
    }

    /* Connect to server */

    if (connect(sockfd,
                (struct sockaddr *)&server_addr,
                sizeof(server_addr)) < 0) {
        perror("connect");
        close(sockfd);
        return 1;
    }

    printf("Connected to %s:%d\n", argv[1], port);

    sock_fp = fdopen(sockfd, "r+");
    if (sock_fp == NULL) {
        perror("fdopen");
        close(sockfd);
        return 1;
    }

    /* Build HTTP request */

    snprintf(http_req, sizeof(http_req),
             "GET /%s HTTP/1.1\r\n"
             "Host: localhost\r\n"
             "Connection: close\r\n"
             "\r\n",
             argv[3]);

    printf("\n===== HTTP Request =====\n");
    printf("%s", http_req);

    /* Send request */

    fputs(http_req, sock_fp);
    fflush(sock_fp);

    /* Open output file */

    file_fp = fopen(argv[3], "wb");
    if (file_fp == NULL) {
        perror("fopen");
        fclose(sock_fp);
        return 1;
    }

    printf("\n===== HTTP Response Headers =====\n");

    /* Read and display HTTP headers */

    while (fgets(line, sizeof(line), sock_fp) != NULL) {

        printf("%s", line);

        if (strcmp(line, "\r\n") == 0)
            break;
    }

    printf("\nDownloading %s ...\n", argv[3]);

    /* Read response body */

    while ((n = fread(buffer, 1, sizeof(buffer), sock_fp)) > 0)
        fwrite(buffer, 1, n, file_fp);

    fclose(file_fp);
    fclose(sock_fp);

    printf("Download complete.\n");

    return 0;
}
