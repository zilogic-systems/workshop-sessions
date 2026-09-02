#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <netdb.h>

#include <stdio.h>
#include <string.h>
#include <error.h>
#include <errno.h>

#define MSG_STRING         "1:%ld:%s:%s:%lu:%s"
#define IPMSG_SENDMSG	   0x00000020UL

int main(int argc, char *argv[])
{
	int sock_fd;
	char buf[1024];
	struct sockaddr_in addr;
	int ret;
	char *msg;
	char *ip;

	/* 1. Parse the user arguments. */
	if (argc != 3) {
		printf("Usage: ipmsg <ip> <msg>\n");
		return 1;
	}
	ip = argv[1];
	msg = argv[2];

	/* 2. Create a UDP socket. */
	sock_fd = socket(PF_INET, SOCK_DGRAM, 0);
	if (sock_fd == -1)
		error(1, errno, "error opening socket");

	/* 3. Create the datagram contents. */
	snprintf(buf, sizeof(buf), MSG_STRING, 1L, "vijay", "computer", 
		 IPMSG_SENDMSG, msg);

	/* 4. Create the destination address */
	addr.sin_family = AF_INET;
	addr.sin_port = htons(2425);
	/* 4a. Convert the IP string into a network ordered IP address. */
	ret = inet_pton(AF_INET, ip, &addr.sin_addr);
	if (ret == 0)
		error(1, 0, "invalid address '%s'", ip);
	if (ret < 0)
		error(1, errno, "invalid address");

	/* 5. Send the datagram. */
	ret = sendto(sock_fd, buf, strlen(buf) + 1, 0, 
		     (struct sockaddr *)&addr, sizeof(addr));
	if (ret == -1)
		error(1, errno, "error sending datagram");

	/* 6. Close the socket. */
	close(sock_fd);

	return 0;
}
