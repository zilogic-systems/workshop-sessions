#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <netdb.h>

#include <stdio.h>
#include <error.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	struct hostent *ent;
	char *hostname;
	struct in_addr *in_addr;
	int i;

	if (argc != 2) {
		printf("Usage: getip <hostname>\n");
		return 1;
	}

	hostname = argv[1];

	ent = gethostbyname(hostname);
	if (ent == NULL)
		error(1, 0, "error getting address for %s: %s", 
		      hostname, hstrerror(h_errno));

	if (ent->h_addrtype != AF_INET)
		error(1, 0, "not an IPv4 address");

	for (i = 0; ent->h_addr_list[i] != NULL; i++) {
		char *sbuf;

		in_addr = (struct in_addr *) ent->h_addr_list[i];
		printf("%08X\n", in_addr->s_addr);
		sbuf = inet_ntoa(*in_addr);
		if (sbuf == NULL)
			error(0, errno, "error converting IP to dotted notation");
		printf("%s\n", sbuf);
	}

	return 0;
}
