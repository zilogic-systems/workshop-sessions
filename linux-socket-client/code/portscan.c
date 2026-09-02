#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>

#include <netdb.h>

#include <stdio.h>
#include <error.h>
#include <errno.h>

char *port_to_name(int port)
{
	struct servent *ent;
	
	ent = getservbyport(port, "tcp");
	if (ent == NULL)
		return "unknown";
	return ent->s_name;
}

int main(int argc, char *argv[])
{
	int sock_fd;
	struct hostent *hostent;
	struct sockaddr_in server_addr;
	struct in_addr server_ip;
	int ret;
	char *server; 
	uint16_t port;
	
	if (argc != 2) {
		printf("Usage: portscan <ip>\n");
		return 1;
	}

	server = argv[1];

	hostent = gethostbyname(server); 
	if (hostent == NULL)
		error(1, 0, "error resolving hostname %s: %s", server, 
		      hstrerror(h_errno));

	server_ip = *((struct in_addr *)hostent->h_addr_list[0]);

	for (port = 0; port < 1024; port++) {
		sock_fd = socket(PF_INET, SOCK_STREAM, 0);
		if (sock_fd == -1)
			error(1, errno, "error opening socket");

		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(port);
		server_addr.sin_addr = server_ip;

		ret = connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
		if (ret == -1) {
			if (errno == ECONNREFUSED) {
				close(sock_fd);
				continue;
			} else if (errno == ETIMEDOUT) {
				printf("%s (%d) Busy\n", port_to_name(htons(port)), port);
			} else {
				error(1, errno, "error connecting to %s", server);
			}
		} else {
			printf("%s (%d) Open\n", port_to_name(htons(port)), port);
		}
		
		close(sock_fd);
	}

	return 0;
}

