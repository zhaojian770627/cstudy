/*
 * tmp.c
 *
 *  Created on: Sep 4, 2016
 *      Author: root
 */

#include <sys/stat.h>
#include <ctype.h>
#include <fcntl.h>
#include "../../lib/tlpi_hdr.h"

int main(int argc, char *argv[]) {
	int fd;
	char template[] = "abcXXXXXX";
	fd = mkstemp(template);
	if (fd == -1)
		errExit("mkstemp");

	printf("Generated filename was: %s\n", template);
	unlink(template);
	if (close(fd) == -1)
		errExit("close");
	exit(EXIT_SUCCESS);
}
