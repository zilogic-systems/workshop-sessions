#include <stdio.h>
#include <errno.h>
#include <error.h>

struct student 
{
	char name[25];
	int marks;
};

#define MAX_STUDENTS 4

int main()
{
	FILE *fp;
	struct student students[MAX_STUDENTS] = {
		{ "Balaji", 92 },
		{ "Naresh", 95 },
		{ "Prabhu", 95 },
		{ "Muthu" , 93 }
	};
	size_t ret;

	fp = fopen("records.dat", "w");
	if (fp == NULL)
		error(1, errno, "error opening records.dat");

	ret = fwrite(students, sizeof(struct student), MAX_STUDENTS, fp);
	if (ret != MAX_STUDENTS) {
		error(1, errno, "error writing to file");
	}

	ret = fclose(fp);
	if (ret == -1)
		error(1, errno, "error closing file");
}
