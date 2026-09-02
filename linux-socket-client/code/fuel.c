#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <netdb.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int sock_fd;
	char buf[1024];
	struct sockaddr_in addr;
	int ret;
	char *level;

	if (argc != 2) {
		puts("Usage: fuel <level>\n");
		exit(1);
	}

	level = argv[1];

	/* 1. Create a UDP socket. */
	sock_fd = socket(PF_INET, SOCK_DGRAM, 0);
	if (sock_fd == -1)
		error(1, errno, "error opening socket");

	/* 2. Create the datagram contents. */
	snprintf(buf, sizeof(buf), "F%d", atoi(level));

	/* 4. Create the destination address */
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5000);

	/* 4a. Convert the IP string into a network ordered IP address. */
	ret = inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
	if (ret == 0)
		error(1, 0, "invalid address");
	if (ret < 0)
		error(1, errno, "invalid address");

	/* 5. Send the datagram. */
	ret = sendto(sock_fd, buf, strlen(buf), 0, 
		     (struct sockaddr *)&addr, sizeof(addr));
	if (ret == -1)
		error(1, errno, "error sending datagram");

	/* 6. Close the socket. */
	close(sock_fd);

	return 0;
}
