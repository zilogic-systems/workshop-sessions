#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	FILE *infp, *outfp;
	int c;

	if (argc < 1)
		fprintf(stderr, "Usage: ccat <filename>");

	infp = fopen(argv[1], "r");

	if (infp == NULL) {
		fprintf(stderr, "Couldn't open a file");
		exit(-1);
	}

	while ((c = fgetc(infp)) != EOF) {

		if (putchar(c) == EOF)
			fprintf(stderr, "standard ouput error");
	}

	if (ferror(infp)) {
		perror("Input file error");
	}

	fclose(infp);

}
