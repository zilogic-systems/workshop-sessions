#include <stdio.h>

int main() 
{
	int ch;

	while (1) {
		ch = fgetc(stdin);
		if (ch == -1)
			break;

		fputc(ch, stdout);
	}
	
	return 0;
}
