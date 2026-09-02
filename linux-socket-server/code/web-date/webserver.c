#include <stdio.h>
#include <time.h>

int main()
{
	time_t tim;

	fputs("HTTP/1.1 200 OK\r\n", stdout);
	fputs("Content-Type: text/plain\r\n\r\n", stdout);

	time(&tim);
	fputs(ctime(&tim), stdout);

	return 0;
}
