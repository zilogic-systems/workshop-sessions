#include <stdio.h>
#include <stdlib.h>

#define NAMELEN 25

struct emp_info_t {
	char name[NAMELEN];
	int no;
} emp_info[5];

int main()
{
	FILE *fp1, *fp2;
	int i = 0, written, read, no;
	struct emp_info_t emp_info1[5];


	fp1 = fopen("data.txt", "w+");
	if (fp1 == NULL) {
		fprintf(stderr, "Couldn't open the file");
		exit(0);
	}

	while (i < 5) {
		printf("enter name:");
		scanf("%s", emp_info[i].name);
		printf("enternumber:");
		scanf("%d", &emp_info[i].no);
		i++;
	}
	written = fwrite(emp_info, sizeof(struct emp_info_t), 5, fp1);

	if (written < 5)
		fprintf(stderr, "Written less than 5 records");

	fclose(fp1);

	fp2 = fopen("data.txt", "r");
	if (fp2 == NULL) {
		fprintf(stderr, "Couldn't open the file");
		exit(0);
	}
	read = fread(emp_info1, sizeof(struct emp_info_t), 5, fp2);
	if (read < 5)
		fprintf(stderr, "Read lss than 5 records");

	printf("Enter record no(<5):");
	scanf("%d", &no);

	if (no > 5)
		no = 5;
	no--;
	printf("Name:%s\n", emp_info1[no].name);
	printf("No:%d\n", emp_info1[no].no);
}
