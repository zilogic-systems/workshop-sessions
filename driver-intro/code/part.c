#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <error.h>
#include <errno.h>
#include <stdint.h>

struct part_record {
	uint8_t active;
	uint8_t discard1[3];
	uint8_t type;
	uint8_t discard2[3];
	uint32_t start;
	uint32_t size;
} __attribute__((packed));

enum {
	KB = 1000,
	MB = 1000 * KB,
	GB = 1000 * MB
};

void print_human_readable(uint64_t val)
{
	if (val > GB) {
		printf("%.1f GB", ((double)val)/GB);
	} else if (val > MB) {
		printf("%.1f MB", ((double)val)/MB);
	} else if (val > KB) {
		printf("%.1f KB", ((double)val)/KB);
	} else {
		printf("%lld bytes", val);
	}
}

int main()
{
	int fd;
	off_t offset;
	ssize_t size;
	char buf[64];
	struct part_record *pr;
	int i;

	fd = open("/dev/sda", O_RDONLY);
	if (fd == -1) {
		error(1, errno, "error opening harddisk device file");
	}

	offset = lseek(fd, 446, SEEK_SET);
	if (offset == -1) {
		error(1, errno, "error seeking harddisk");
	}

	size = read(fd, buf, sizeof(buf));
	if (size == -1) {
		error(1, errno, "error reading harddisk");
	}

	pr = (struct part_record *) buf;

	for (i = 0; i < 4; i++) {
		printf("%d\t", i+1);
		print_human_readable(pr[i].start * 512ULL);
		printf("\t\t");
		print_human_readable(pr[i].size * 512ULL);
		printf("\n");
	}
	
	return 0;
}
