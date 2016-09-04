/*
 * lseek.c
 *
 *  Created on: Sep 4, 2016
 *      Author: root
 */

#include <sys/stat.h>
#include <fcntl.h>
#include "../../lib/tlpi_hdr.h"

int main(int argc, char *argv[]) {
	int fd1, fd2;
	int flag1, flag2;
	off_t offset;
	fd1 = open("a.txt", O_RDWR | O_CREAT,
	S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

	if (fd1 == -1)
		errExit("open a.txt");

	fd2 = dup(fd1);
	if (fd2 == 1)
		errExit("dup");

	lseek(fd1, 3, SEEK_SET);
	offset = lseek(fd2, 0, SEEK_CUR);
	printf("fd2 offset %ld \n", offset);

	flag1 = fcntl(fd1, F_GETFL);
	flag2 = fcntl(fd2, F_GETFL);
	printf("fd1 flag %d \n", flag1);
	printf("fd2 flag %d \n", flag2);

	if (close(fd1) == -1)
		errExit("Close fd1");

	if (close(fd2) == -1)
		errExit("Close fd2");
	exit(EXIT_SUCCESS);
}
