#include <signal.h>
#include <stdio.h>
#include <unistd.h>

long long a;

void inc()
{
	long long old;
	long long new;
	
	old = a;
	a = a + 1;
	new = a;
	
	if (new != old+1)
		printf("Error! Expected %lld got %lld\n", old+1, new);
}

void signal_handler(int signum)
{
	inc();
	/* Reschedule the timer. */
	alarm (1);
}

int main (void)
{
	sigset_t alrm_mask;
	sigset_t old_mask;

	signal (SIGALRM, signal_handler);

	/* Create a mask with the alarm signal set. */
	sigemptyset(&alrm_mask);
	sigaddset(&alrm_mask, SIGALRM);

	/* Start the timer. SIGALRM will occur every second. */
	alarm (1);
	
	while (1) {
		/* Mask the alarm signal, and save the original set. */
		sigprocmask(SIG_BLOCK, &alrm_mask, &old_mask);

		inc();

		/* Restore the original set. */
		sigprocmask(SIG_SETMASK, &old_mask, NULL);
	}
}
