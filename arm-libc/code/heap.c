#include <sys/stat.h>

extern char heap_low; /* Defined by the linker */
extern char heap_top; /* Defined by the linker */

char *heap_end = &heap_low;

caddr_t _sbrk(int incr) {
	char *prev_heap_end;
/*
	if (heap_end == 0) {
		heap_end = &heap_low;
	}
*/
	prev_heap_end = heap_end;

	if ((heap_end + incr) > &heap_top) {
		/* Heap and stack collision */
		return (caddr_t)0;
	}

	heap_end += incr;
	return (caddr_t) prev_heap_end;
}
