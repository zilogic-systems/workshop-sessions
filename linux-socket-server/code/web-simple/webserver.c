#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <errno.h>
#include <string.h>

char *err_html = "HTTP/1.1 %d %s\r\n\
Content-Type: text/html\r\n	    \
\r\n				    \
<html><body>                        \
<h1>Error %d: %s</h1>               \
<hr>                                \
Simple Web Server                   \
</body></html>\n";

void http_error(int code, char *err)
{
	fprintf(stdout, err_html, code, err, code, err);
}

int main()
{
	char buf[1024];
	char *ret;
	char *file, *end;
	int fd;
	int dir = 0;

	ret = fgets(buf, sizeof(buf), stdin);
	if (ret == NULL)
		return 1;

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
