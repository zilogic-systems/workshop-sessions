#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <error.h>

/* Mapping from signal nos. to signal names. */
char *signal_str[] = { 
	[SIGHUP]  = "HUP",  [SIGINT]  = "INT",
	[SIGQUIT] = "QUIT", [SIGILL]  = "ILL",
	[SIGABRT] = "ABRT", [SIGFPE]  = "FPE",
	[SIGKILL] = "KILL", [SIGSEGV] = "SEGV",
	[SIGPIPE] = "PIPE", [SIGALRM] = "ALRM",
	[SIGTERM] = "TERM", [SIGUSR1] = "USR1",
	[SIGUSR2] = "USR2", [SIGCHLD] = "CHLD",
	[SIGCONT] = "CONT", [SIGSTOP] = "STOP",
	[SIGTSTP] = "TSTP", [SIGTTIN] = "TTIN",
	[SIGTTOU] = "TTOU"
};

int signal_atoi(char *str_sig)
{
	int nsignals;
	int sig;

	nsignals = sizeof(signal_str)/sizeof(signal_str[0]);
	for (sig = 0; sig < nsignals; sig++) {
		if (signal_str[sig] != NULL
		    && strcmp(signal_str[sig], str_sig) == 0)
			break;
	}

	if (sig == nsignals)
		error(1, errno, "invalid signal name '%s'", str_sig);

	return sig;
}

int main(int argc ,char *argv[])
{
	pid_t pid;
	int sig;
	int ret;

	if (argc < 3) {
		printf("Usage: kill <signal> <pid>\n");
		return 1;
	}

	sig = signal_atoi(argv[1]);
	pid = atoi(argv[2]);

	ret = kill(pid, sig);
	if (ret == -1)
		error(1, errno, "error sending sig %d to %u", sig, pid);

	return 0;
}
