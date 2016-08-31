/*
 * dtee.c
 *
 *  Created on: Aug 22, 2016
 *      Author: root
 */

#include <sys/stat.h>
#include <ctype.h>
#include <fcntl.h>
#include "../lib/tlpi_hdr.h"

#ifndef BUF_SIZE	/* Allow "cc -D" to override definition */
#define BUF_SIZE 1024
#endif

int main(int argc, char *argv[]) {
	int fd, opt;
	ssize_t numRead;
	char buf[BUF_SIZE + 1];
	off_t offset;

	if (argc < 2 || strcmp(argv[1], "--help") == 0)
		usageErr("%s [-a] file");

	/* Open input and output files */
	fd = open(argv[argc - 1], O_RDWR | O_CREAT,
	S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (fd == -1)
		errExit("open");

	offset = lseek(fd, 0, SEEK_SET);

	while ((opt = getopt(argc, argv, ":a")) != -1) {
		switch (opt) {
		case 'a':
			offset = lseek(fd, -1, SEEK_END);
			break;

		case '?':
		default:
			fprintf(stderr, "%s option: '-%c' is invalid:ignore\n", argv[0],
					optopt);
		}
	}

	while ((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0) {
		buf[numRead] = '\0';

		if (write(STDOUT_FILENO, buf, numRead) != numRead)
			fatal("couldn;t write whild buf");
		if (write(fd, buf, numRead) != numRead)
			fatal("couldn;t write whild buf");
	}

	if (numRead == -1)
		errExit("read");

	if (close(fd) == -1)
		errExit("Close input");

	exit(EXIT_SUCCESS);
}
