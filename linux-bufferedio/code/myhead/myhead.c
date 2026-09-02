#include <stdio.h>
#include <error.h>

int main()
{
	int i;
	int nlines;
	char buf[256];
	char *retp;
	int ret;

	nlines = 10;

	for (i = 0; i < nlines; i++) {
		retp = fgets(buf, sizeof(buf), stdin);
		if (retp == NULL) {
			if (feof(stdin))
				break;
			else
				error(1, 0, "error reading stdin");
		}
		
		ret = fputs(buf, stdout);
		if (ret == EOF)
			error(1, 0, "error writing to stdout");
	}
}
