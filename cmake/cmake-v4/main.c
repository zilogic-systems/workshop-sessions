#include <stdio.h>

int add(int a, int b);
int sub(int a, int b);

void main()
{
	int a = 5;
	int b = 3;
	int sum;
	int diff;

	sum = add(a, b);
	diff = sub(a, b);

	printf("Sum = %d\n", sum);
	printf("Diff = %d\n", diff);
}
