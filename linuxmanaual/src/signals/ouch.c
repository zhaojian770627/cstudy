/*
 * ouch.c
 *
 *  Created on: Oct 19, 2016
 *      Author: root
 */
#include <signal.h>
#include "../lib/tlpi_hdr.h"

static void sigHandler(int sig) {
	printf("Ouch!\n");
}

int main(int argc, char **argv) {
	int j;
	if (signal(SIGINT, sigHandler) == SIG_ERR)
		errExit("signal");
	for (j = 0;; j++) {
		printf("%d\n", j);
		sleep(3);
	}
	exit(EXIT_SUCCESS);
}
