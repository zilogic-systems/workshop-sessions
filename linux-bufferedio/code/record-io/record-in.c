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
	int ret;
	struct student student;

	fp = fopen("records.dat", "r");
	if (fp == NULL)
		error(1, errno, "error opening records.dat");

	while (1) {
		ret = fread(&student, sizeof(struct student), 1, fp);
		if (ret != 1) {
			if (ferror(fp))
				error(1, errno, "error writing to file");
			else
				break;
		}

		printf("Name: %s\n", student.name);
		printf("Marks: %d\n", student.marks);
	}

	ret = fclose(fp);
	if (ret == -1)
		error(1, errno, "error closing file");
}
