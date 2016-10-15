/*
 * s2.c
 *
 *  Created on: Oct 15, 2016
 *      Author: root
 */
#include <limits.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "../../lib/tlpi_hdr.h"

#define BUF_SIZE PATH_MAX

/**
 * test 18-2
 * copy myfile to .. may success
 */
int main(int argc, char **argv) {
	int fd;
	struct stat statbuf;
	char buf[BUF_SIZE];
	ssize_t numBytes;

	mkdir("test", S_IRUSR | S_IWUSR | S_IXUSR);
	chdir("test");
	fd = open("myfile", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	symlink("myfile", "../mylink");

	if (lstat("../mylink", &statbuf) == -1)
		errExit("lstat");

	if (!S_ISLNK(statbuf.st_mode))
		fatal("%s is not a symbolic link", "../mylink");

	numBytes = readlink("../mylink", buf, BUF_SIZE - 1);
	if (numBytes == -1)
		errExit("readlink");
	buf[numBytes] = '\0';
	printf("readlink:%s-->%s\n", "../mylink", buf);

	if (realpath("../mylink", buf) == NULL)
		errExit("realpath");
	printf("realpath:%s-->%s\n", "../mylink", buf);
	chmod("../mylink", S_IRUSR);
	exit(EXIT_SUCCESS);
}
