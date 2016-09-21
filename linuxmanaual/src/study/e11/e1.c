/*
 * e1.c
 *
 *  Created on: Sep 21, 2016
 *      Author: root
 */
#include <dirent.h>
#include "../../lib/tlpi_hdr.h"

int main(int argc, char *argv[]) {
	if (argc < 2 || strcmp(argv[1], "--help") == 0)
		usageErr("%s <username> \n", argv[0]);

	DIR *dirp;
	struct dirent *dp;
	char dirpath[] = "/proc";
	dirp = opendir(dirpath);
	if (dirp == NULL) {
		errMsg("opendir failed on '%s'", dirpath);
	}
	for (;;) {	// To distinguish error from end-of-directory
		errno = 0;
		dp = readdir(dirp);
		if (dp == NULL)
			break;

		if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
			continue;
		printf("%s/", dirpath);
		printf("%s/", dp->d_name);
	}

	if (errno != 0)
		errExit("readdir");
	if (closedir(dirp) == -1)
		errMsg("closedir");

	exit(EXIT_SUCCESS);
}
