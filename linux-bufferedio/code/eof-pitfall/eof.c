#include <stdio.h>

int main()
{
	while (!feof(stdin)) {
		char buf[16];

		fgets(buf, sizeof(buf), stdin);
		fputs(buf,stdout);
	}

	return 0;
}
