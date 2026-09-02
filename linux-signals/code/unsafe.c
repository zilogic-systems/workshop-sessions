#include <signal.h>
#include <stdio.h>
#include <unistd.h>

long long a;

void inc()
{
	int i;
	long long old;
	long long new;
	
	old = a;
	a = a + 1;

	/* Adding a delay here to increase the probability of the ALARM signal occuring at this point */
	for (i = 0; i < 10000; i++);

	new = a;

	if (new != old+1)
		printf("Error! Expected %lld got %lld\n", old+1, new);
}

void signal_handler(int signum)
{
	inc();
	/* Reschedule the timer. */
	alarm(1);
}

int main (void)
{
	int i;
	
	signal(SIGALRM, signal_handler);
	/* Start the timer. SIGALRM will occur every second. */
	alarm(1);
	
	while (1) {
		inc();
	}
}
