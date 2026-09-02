#include <sys/types.h>
#include <sys/socket.h>

#include <unistd.h>
#include <netdb.h>

#include <stdio.h>
#include <error.h>
#include <errno.h>

#define DAYTIME_PORT 13

int main()
{
	int sock_fd;
	int ret;
	char buf[256];

	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(DAYTIME_PORT);

	/* 1. Create a TCP socket. */
	sock_fd = socket(PF_INET, SOCK_STREAM, 0);
	if (sock_fd == -1)
		error(1, errno, "error opening socket");
	
	/* 2. Establish a TCP connection to the server. */
	ret = connect(sock_fd, (struct sockaddr *) &saddr,
		      sizeof(saddr));
	if (ret == -1)
		error(1, errno, "error connecting to server");

	/* 3. Read the date and time sent by the server. */
	while (1) {
		int i;

		ret = read(sock_fd, buf, sizeof(buf));
		if (ret == -1)
			error(1, errno, "error reading socket");
		else if (ret == 0)
			break;
		else
			for (i = 0; i < ret; i++) 
				putchar(buf[i]);
	}

	/* 4. Close the connection. */
	close(sock_fd);

	return 0;
}
