/*
 * e1.c
 *
 *  Created on: Sep 21, 2016
 *      Author: root
 */
#include <dirent.h>
#include <fcntl.h>
#include "../../lib/tlpi_hdr.h"

#define CHARMAX 1024

int main(int argc, char *argv[]) {
	if (argc < 2 || strcmp(argv[1], "--help") == 0)
		usageErr("%s <username> \n", argv[0]);

	DIR *dirp;
	struct dirent *dp;
	char dirpath[] = "/proc";
	char pathName[CHARMAX];
	char buffer[CHARMAX];
	FILE *input;

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
		int i = strtol(dp->d_name, NULL, 10);
		if (i != 0L) {

			sprintf(pathName, "/proc/%s/status", dp->d_name);
			pathName[strlen(pathName)] = '\0';

			input = fopen(pathName, "r");
			if (input == NULL) {
				printf("open %s error", pathName);
				continue;
			}

			while (fgets(buffer, CHARMAX, input) != NULL) {
				if (strncmp(buffer, "Name:", 5) == 0){
					printf("%s", buffer);
					break;
				}
			}

			printf("open %s \n", pathName);

			if (fclose(input) != 0)
				printf("close %s error", pathName);
		}
	}

	if (errno != 0)
		errExit("readdir");
	if (closedir(dirp) == -1)
		errMsg("closedir");

	exit(EXIT_SUCCESS);
}
