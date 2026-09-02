#include <stdio.h>

int main()
{
	char str[20];
	char *retp;

	puts("Enter '100%success' as input");
	retp = fgets(str, sizeof(str), stdin);
	if (retp == NULL)
		return 1;

	printf(str);
	printf("\n");

	return 0;
}
