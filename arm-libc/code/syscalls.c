/* ### START: syscalls.full */

/* ### START: syscalls.dummy1 */

#include <sys/stat.h>

#define UART_TX_REG (*(unsigned int *)0x40100000)

int _lseek(int fd, int ptr, int dir)
{
	return 0;
}

int _open(const char *name, int flags, int mode)
{
	return -1;
}

int _close(int fd)
{
	return -1;
}
/* ### END: syscalls.dummy1 */

/* ### START: syscalls.dummy2 */
int _read(int fd, char *ptr, int len)
{
	return -1;
}

int _sbrk(int inc) __attribute__((weak));
int _sbrk(int inc)
{
	return -1;
}

/* ### END: syscalls.dummy2 */

/* ### START: syscalls.dummy3 */
int _fstat(int fd, struct stat *st)
{
	st->st_mode = S_IFCHR;
	return 0;
}

int _isatty(int fd)
{
	return 1;
}

/* ### END: syscalls.dummy3 */

/* ### START: syscalls.defined */

int _write(int fd, char *ptr, int len)
{
	int count;

	for (count = 0; count < len; count++) {
		UART_TX_REG = *(ptr + count);
	}

	return count;
}
/* ### END: syscalls.defined */
/* ### END: syscalls.full */
