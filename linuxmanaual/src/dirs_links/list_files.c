/*
 * list_files.c
 *
 *  Created on: Oct 14, 2016
 *      Author: root
 */

#include <dirent.h>
#include "../lib/tlpi_hdr.h"

/*
 * List all files in directory 'dirPath'
 */
static void listFiles(const char *dirpath) {
	DIR *dirp;
	struct dirent *dp;
	Boolean isCurrent;	// True if 'dirpath' is "."

	isCurrent = strcmp(dirpath, ".");

	dirp = opendir(dirpath);
	if (dirp == NULL) {
		errMsg("opendir failed on '%s'", dirpath);
		return;
	}

	// For each entry in this directory,print directory+filename
	for (;;) {
		errno = 0;
		dp = readdir(dirp);
		if (dp == NULL)
			break;

		if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
			continue;

		if (!isCurrent)
			printf("%s/", dirpath);
		printf("%s\n", dp->d_name);
	}

	if (errno != 0)
		errExit("readdir");

	if (closedir(dirp) == -1)
		errMsg("closedir");
}

int main(int argc, char *argv[]) {
	if (argc > 1 && strcmp(argv[1], "--help") == 0)
		usageErr("%s [dir...\n", argv[0]);

	if (argc == 1)
		listFiles(".");
	else
		for (argv++; *argv; argv++)
			listFiles(*argv);
	exit(EXIT_SUCCESS);
}
