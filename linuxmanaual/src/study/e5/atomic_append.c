/*
 * dtee.c
 *
 *  Created on: Aug 22, 2016
 *      Author: root
 */

#include <sys/stat.h>
#include <ctype.h>
#include <fcntl.h>
#include "../../lib/tlpi_hdr.h"

int main(int argc, char *argv[]) {
	int fd, flags, numBytes, i;

	if (argc < 3 || strcmp(argv[1], "--help") == 0)
		usageErr("%s filename numbytes [x]");

	Boolean hasX = FALSE;
	if (argc == 4 && strcmp(argv[3], "x") == 0)
		hasX = TRUE;

	if (hasX)
		flags = O_RDWR | O_CREAT;
	else
		flags = O_RDWR | O_CREAT | O_APPEND;

	fd = open(argv[1], flags,
	S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

	if (fd == -1)
		errExit("open");

	numBytes = getInt(argv[2], 0, "numbytes");

	for (i = 0; i < numBytes; i++) {
		if (hasX)
			lseek(fd, 0, SEEK_END);

		if (write(fd, "X", 1) != 1)
			fatal("couldn't write [X]");
	}

	if (close(fd) == -1)
		errExit("Close input");

	exit(EXIT_SUCCESS);
}
