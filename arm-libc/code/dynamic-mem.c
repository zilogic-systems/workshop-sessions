#include <stdio.h>

int main()
{
	char *text = "Malloc Tested";
	char *p;

	p = malloc(15);

	if (p == NULL)
		return -1;

	memset(p, 0, 15);
	memcpy(p, text, strlen(text));

	printf("%s\n", p);
}
