#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <netinet/in.h>
#include <netinet/ip.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <error.h>

char *err_html = "HTTP/1.1 %d %s\r\n\
Content-Type: text/html\r\n\r\n     \
<html><body>                        \
<h1>Error %d: %s</h1>               \
<hr>                                \
Simple Web Server                   \
</body></html>\n";

void http_error(int code, char *err)
{
	fprintf(stdout, err_html, code, err, code, err);
}

int handle_http()
{
	char buf[1024];
	char *ret;
	char *file, *end;
	int fd;
	int dir = 0;

	ret = fgets(buf, sizeof(buf), stdin);
	if (ret == NULL)
		return 1;

	fputs(buf, stderr);

	if (strncmp(buf, "GET", 3) != 0) {
		http_error(501, "Not Implemented");
		return 1;
	}

	file = index(buf, ' ');
	if (file == NULL) {
		http_error(400, "Bad Request");
		return 1;
	}
	file++;

	end = index(file, ' ');
	if (end == NULL) {
		http_error(400, "Bad Request");
		return 1;
	}
	*end = '\0';

	fd = open(file, O_RDWR);
	if (fd == -1) {
		if (errno == EISDIR) {
			dir = 1;
		} else {
			http_error(500, strerror(errno));
			return 1;
		}
	}
	close(fd);

	fputs("HTTP/1.1 200 OK\r\n", stdout);
	fputs("Content-Type: text/plain\r\n\r\n", stdout);

	if (dir == 1) {
		execl("/bin/ls", "ls", "-a", "-p", file, NULL);
		return 1;
	} else {
		execl("/bin/cat", "cat", file, NULL);
		return 1;
	}

	return 0;
}

int main()
{
	int listen_fd;
	int sock_fd;
	int ret;

	struct sockaddr_in myaddr;
	struct sockaddr_in client_addr;

	listen_fd = socket(PF_INET, SOCK_STREAM, 0);
	if (listen_fd == -1)
		error(1, errno, "error creating socket");
	
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(8085);
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	ret = bind(listen_fd, (struct sockaddr *) &myaddr, sizeof(myaddr));
	if (ret == -1)
		error(1, errno, "error binding to port 8085");

	ret = listen(listen_fd, 10);
	if (ret == -1)
		error(1, errno, "error listening on socket");

	while (1) {
		pid_t pid;
		socklen_t len;

		len = sizeof(client_addr);
		sock_fd = accept(listen_fd, 
				 (struct sockaddr *)
				 &client_addr, &len);
		if (sock_fd == -1)
			error(1, errno, 
			      "error accepting connections");

		pid = fork();
		if (pid == 0) {
			/* Child */
			dup2(sock_fd, 0);
			dup2(sock_fd, 1);
			
			ret = handle_http();
			exit(ret);
		} else {
 			close(sock_fd);
		}
	}
}
