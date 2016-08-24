/*
 * copy.c
 *
 *  Created on: Aug 22, 2016
 *      Author: root
 */

#include <sys/stat.h>
#include <fcntl.h>
#include "../lib/tlpi_hdr.h"

#ifndef BUF_SIZE	/* Allow "cc -D" to override definition */
#define BUF_SIZE 1024
#endif

int main(int argc, char *argv[]) {
	int inputFd;
	ssize_t numRead;
	char buf[BUF_SIZE + 1];

	if (argc != 2 || strcmp(argv[1], "--help") == 0)
		usageErr("%s filename \n", argv[0]);

	/* Open input and output files */
	inputFd = open(argv[1], O_RDONLY);
	if (inputFd == -1)
		errExit("opening file %s", argv[1]);

	/* Transfer data until we encounter end of input or an error */
	while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0) {
		if (numRead == -1)
			errExit("read");

		buf[numRead] = '\0';
		printf(buf);
	}

	if (close(inputFd) == -1)
		errExit("Close input");

	exit(EXIT_SUCCESS);
}
