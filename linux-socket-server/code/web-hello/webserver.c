#include <stdio.h>

int main()
{
	fputs("HTTP/1.1 200 OK\r\n", stdout);
	fputs("Content-Type: text/plain\r\n\r\n", stdout);

	fputs("Hello World", stdout);

	return 0;
}
