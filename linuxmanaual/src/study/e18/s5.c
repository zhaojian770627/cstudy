/*
 * s5.c
 *
 *  Created on: Oct 15, 2016
 *      Author: root
 */
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include "../../lib/tlpi_hdr.h"

#define BUF_SIZE PATH_MAX
char path[BUF_SIZE] = "";

void getpath() {
	DIR *dirp;
	struct dirent *dp;
	int curFd, cFd, pFd;
	int inode, pinode;
	char curName[BUF_SIZE];
	struct stat statbuf;

	curFd = -1;

	for (;;) {
		// readCurrent
		cFd = open(".", O_RDONLY);
		if (cFd == -1)
			errExit("opening .");

		if (curFd == -1)
			curFd = cFd;

		if (fstat(cFd, &statbuf) == -1)
			errExit("fstat");

		inode = statbuf.st_ino;

		pFd = open("..", O_RDONLY);
		if (pFd == -1)
			errExit("opening ..");

		if (fstat(pFd, &statbuf) == -1)
			errExit("fstat");

		pinode = statbuf.st_ino;

		if (pinode == inode) {
			break;
		}

		dirp = opendir("..");

		if (dirp == NULL) {
			errExit("opendir");
		}

		for (;;) {
			errno = 0;
			dp = readdir(dirp);
			if (dp == NULL)
				break;

			if (dp->d_ino == inode) {
				strcpy(curName, path);
				strcpy(path, "/");
				strcat(path, dp->d_name);
				strcat(path, curName);
				break;
			}
			continue;
		}

		fchdir(pFd);

		//close
		if (closedir(dirp) == -1)
			errMsg("closedir");

		if (close(pFd) == -1)
			errExit("Close pFD");

		if (curFd != cFd)
			if (close(cFd) == -1)
				errExit("Close cFD");
	}
	if(fchdir(curFd)==-1)
		errExit("fchdir");
	if (close(curFd) == -1)
		errExit("close curFd");
}

int main(int argc, char **argv) {
	getpath();
	printf("%s\n", path);
	exit(EXIT_SUCCESS);
}
