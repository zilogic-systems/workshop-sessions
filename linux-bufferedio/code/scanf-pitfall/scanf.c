#include <stdio.h>

int main()
{
	char str1[16], str2[16] = "don't corrupt m";

	printf("Enter string longer than 16 characters: ");
	scanf("%15s", str1);

	printf("First String: (%s)\n", str1);
	printf("Second String: (%s)\n", str2);

	return 0;
}
