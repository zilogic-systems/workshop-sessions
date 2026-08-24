#include <stdio.h>

int add(int a, int b);
int sub(int a, int b);

int main(void)
{
	int a = 3;
	int b = 2;
	int result;
	
	result = add(a, b);
	printf("Sum: %d\n", result);

	result = sub(a, b);
	printf("Difference: %d\n", result);

	return 0;
}
