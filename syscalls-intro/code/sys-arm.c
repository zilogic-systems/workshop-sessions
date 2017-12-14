#include <unistd.h>
#include <stdio.h>

#define __asm_syscall(...) do { \
	__asm__ __volatile__ ( "svc 0" \
	: "=r"(r0) : __VA_ARGS__ : "memory"); \
	return r0; \
	} while (0)

#define CHMOD 15

static inline long __syscall0(long n)
{
	register long r7 __asm__("r7") = n;
	register long r0 __asm__("r0");
	__asm_syscall("r"(r7));
}

static inline long __syscall2(long n, char *a, long b)
{
	register long r7 __asm__("r7") = n;
	register char* r0 __asm__("r0") = a;
	register long r1 __asm__("r1") = b;
	__asm_syscall("r"(r7), "0"(r0), "r"(r1));
}

int main()
{
	int rc;

	rc = __syscall2(CHMOD, "/home/user/a.txt", 0777);

	if (rc != -1)
		printf("Permission Changed\n");
	else
		printf("Error\n");
}
