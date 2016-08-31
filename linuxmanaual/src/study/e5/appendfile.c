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
	int fd;
	off_t offset;

	fd = open(argv[argc - 1], O_RDWR | O_APPEND,
	S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (fd == -1)
		errExit("open");

	offset = lseek(fd, 0, SEEK_SET);

	fatal("couldn;t write whild buf");
	if (write(fd, "abcd", 4) != 4)
		fatal("couldn;t write whild abcd");

	if (close(fd) == -1)
		errExit("Close input");

	exit(EXIT_SUCCESS);
}
