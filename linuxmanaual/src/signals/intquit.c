/*
 * ouch.c
 *
 *  Created on: Oct 19, 2016
 *      Author: root
 */
#include <signal.h>
#include "../lib/tlpi_hdr.h"

static void sigHandler(int sig) {
	static int count = 0;

	/* UNSAFE:This handler uses non-ayync-signal-safe functions
	 * (printf(),exit(); see Section 21.1.2
	 */

	if (sig == SIGINT) {
		count++;
		printf("Caught SIGINT (%d)\n", count);
		// Resume execution at point of interruption
		return;
	}

	// Must be SIGQUIT - print a message and terminate the process
	printf("Caught SIGQUIT - that's all folks!\n");
	exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
	if (signal(SIGINT, sigHandler) == SIG_ERR)
		errExit("signal");

	if (signal(SIGQUIT, sigHandler) == SIG_ERR)
		errExit("signal");

	for (;;)
		pause();

	exit(EXIT_SUCCESS);
}
