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
	char *server = "time-a.nist.gov";
	int sock_fd;
	struct hostent *hostent;
	struct sockaddr_in server_addr;
	int ret;
	int i;
	char buf[256];

	/* 1. Create a TCP socket. */
	sock_fd = socket(PF_INET, SOCK_STREAM, 0);
	if (sock_fd == -1)
		error(1, errno, "error opening socket");
	
	/* 2. Convert the host name to an IP address. */
	hostent = gethostbyname(server); 
	if (hostent == NULL)
		error(1, 0, "error resolving hostname %s: %s", server, 
		      hstrerror(h_errno));

	/* 3. Create a socket address structure with the server address and port no. */
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(DAYTIME_PORT);
	server_addr.sin_addr = *((struct in_addr *)hostent->h_addr_list[0]);

	/* 4. Establish a TCP connection to the server. */
	ret = connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if (ret == -1)
		error(1, errno, "error connecting to %s", server);

	/* 5. Read the date and time sent by the server. */
	while (1) {
		ret = read(sock_fd, buf, sizeof(buf));
		if (ret == -1)
			error(1, errno, "error reading socket");
		else if (ret == 0)
			break;
		else
			for (i = 0; i < ret; i++) 
				putchar(buf[i]);
	}

	/* 6. Close the connection. */
	ret = close(sock_fd);
	if (ret == -1)
		error(1, errno, "error shutting socket");

	return 0;
}
