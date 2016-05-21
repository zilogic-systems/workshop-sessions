#include <sys/stat.h>

extern char heap_low; /* Defined by the linker */
extern char heap_top; /* Defined by the linker */

char *prog_break = &heap_low;

caddr_t _sbrk(int incr) {
	char *prev_prog_break;
	
	prev_prog_break = prog_break;

	if ((prog_break + incr) > &heap_top) {
		return (caddr_t)0;
	}

	prog_break += incr;
	return (caddr_t) prev_prog_break;
}
