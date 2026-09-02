#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <netinet/ip.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <error.h>

#define IPMSG_SCAN 0x01

void handle_message(char *buf, int sock_fd, struct sockaddr_in *client_addr)
{
	char *msg;
	char *type;
	char *ip;
	char *user;
	char *seq;
	int ret;

	char send_msg[1024];

	printf("%s\n", buf);

	/* 1. Split entire message to seq, user, ip, type, msg */
	msg = rindex(buf, ':');
	if (msg == NULL)
		return;
	*msg = '\0';

	type = rindex(buf, ':');
	if (type == NULL)
		return;
	*type = '\0';
	
	ip = rindex(buf, ':');
	if (ip == NULL)
		return;
	*ip = '\0';
	
	user = rindex(buf, ':');
	if (user == NULL)
		return;
	*user = '\0';

	seq = rindex(buf, ':');
	if (seq == NULL)
		return;
	*seq = '\0'; 
	
	/* 2. The pointers point to the delimiter, increment to point
	 * to the value. 
	 */
	msg++;
	type++;
	ip++;
	user++;
	seq++;

	/* 3. Check message type. */
	if (atol(type) & IPMSG_SCAN) {
		/* 3a. If scan, create response with our username. */
		snprintf(send_msg, sizeof(send_msg), 
			 "1:2:vijaykumar:computer:3:vijaykumar");
	} else {

		/* 3b. If message, create response with
		 * acknowledgment, and print message. 
		 */
		snprintf(send_msg, sizeof(send_msg),
			 "1:2:vijaykumar:computer:33:%s", seq);

		printf("Message from %s@%s: \"%s\"\n", user, ip, msg);
	}

	/* 4. Send the response to IP from which we got the
	 * datagram. 
	 */
	ret = sendto(sock_fd, send_msg, strlen(send_msg) + 1, 0,
		     (struct sockaddr *)client_addr, sizeof(*client_addr));
	if (ret == -1)
		error(1, errno, "error sending packet");
}

int main()
{
	int sock_fd;
	int ret;
	char buf[1024];

	struct sockaddr_in myaddr;
	struct sockaddr_in client_addr;

	/* 1. Create a socket. */
	sock_fd = socket(PF_INET, SOCK_DGRAM, 0);
	if (sock_fd == -1)
		error(1, errno, "error creating socket");
	
	/* 2. Bind to port 2425 */
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(2425);
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	ret = bind(sock_fd, (struct sockaddr *) &myaddr, sizeof(myaddr));
	if (ret == -1)
		error(1, errno, "error binding to port 2425");

	/* 3. Wait for IP Messenger datagrams and respond. */
	while (1) {
		pid_t pid;
		socklen_t len;
		
		len = sizeof(client_addr);
		ret = recvfrom(sock_fd, buf, sizeof(buf), 0,
			       (struct sockaddr *)&client_addr, &len);
		if (ret == -1)
			error(1, errno, "error receiving data");
		
		buf[ret] = '\0';
		handle_message(buf, sock_fd, &client_addr);
	}
}
