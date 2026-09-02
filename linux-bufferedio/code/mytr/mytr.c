#include <stdio.h>
#include <error.h>

int main()
{
	char from, to;
	int ch;

	from = 'a';
	to = 'e';

	while (1) {
		ch = fgetc(stdin);
		if (ch == -1) {
			if (ferror(stdin))
				error(1, 0, "error occurred while reading stdin");
			else
				break;
		}

		if (ch == from) 
			ch = to;

		ch = fputc(ch, stdout);
		if (ch == EOF) 
			error(1, 0, "error ocurred while writing stdout");
	}
	
	return 0;
}
