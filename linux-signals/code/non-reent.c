#define STRING_SIZE_LIMIT 64

#include <signal.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>

char *strtoupper(char *str)
{
        /* Returning pointer to static data makes it non-reentrant */
	static char buffer[STRING_SIZE_LIMIT];
	int index;
       
	for (index = 0; str[index]; index++)
                buffer[index] = toupper(str[index]);
	buffer[index] = '\0';
	return buffer;
}

void signal_handler(int signum)
{
	strtoupper("Hello");
	/* Reschedule the timer. */
	alarm (1);
}

int main (void)
{
	signal (SIGALRM, signal_handler);
	/* Start the timer. SIGALRM will occur every second. */
	alarm (1);
	
	while (1) {
		char *upper = strtoupper("non reentrant world");
		if (strcmp(upper, "NON REENTRANT WORLD") != 0)
			printf("Error %s, expected NON REENTRANT WORLD\n", upper);
	}
}
