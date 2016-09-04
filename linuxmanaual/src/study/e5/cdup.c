/*
 * cdup.c
 *
 *  Created on: Sep 4, 2016
 *      Author: root
 */
#include <sys/stat.h>
#include <fcntl.h>
#include "../../lib/tlpi_hdr.h"

int Dup(int oldfd);
int Dup2(int oldfd, int newfd);

int main(int argc, char *argv[]) {
	int fd;
	int newfd;
	if ((fd = open("a.txt", O_RDONLY)) == 1)
		errExit("open");

	newfd = Dup(fd);
	if (newfd == -1)
		errExit("Dup");

	printf("old fd is %d,new fd is %d\n", fd, newfd);

	printf("Input the new fd:");
	scanf("%d",&newfd);

	newfd=Dup2(fd,newfd);
	if(newfd==-1)
		errExit("Dup2");

	printf("old fd is %d,new fd is %d\n", fd, newfd);
	exit(EXIT_SUCCESS);
}

int Dup(int oldfd) {
	int newfd = fcntl(oldfd, F_DUPFD, oldfd + 1);
	return newfd;
}

int Dup2(int oldfd, int newfd) {
	int fd = newfd;
	// oldfd is valid
	if (fcntl(oldfd, F_GETFL) == -1) {
		errno = EBADF;
		return -1;
	}

	if (oldfd == newfd)
		return newfd;

	if (fcntl(newfd, F_GETFL) != -1)
		close(newfd);

	newfd = fcntl(oldfd, F_DUPFD, fd);
	if (newfd != fd)
		newfd = fcntl(oldfd, F_SETFD, fd);
	return newfd;
}
