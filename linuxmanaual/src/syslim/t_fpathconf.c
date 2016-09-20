/*
 * t_fpathconf.c
 *
 *  Created on: Sep 20, 2016
 *      Author: root
 */

#include "../lib/tlpi_hdr.h"

static void fpathconfPrint(const char *msg, int fd, int name) {
	long lim;
	errno = 0;

	lim = fpathconf(fd, name);
	if (lim != -1) {	// Call succeeded,limit determinate
		printf("%s %ld\n", msg, lim);
	} else {
		if (errno == 0)	// Call successed,limit indeterminate
			printf("%s (indeterminate)\n", msg);
		else
			errExit("fpathconf %s", msg);
	}
}

int main(int argc, char *argv[]) {
	fpathconfPrint("_PC_NAME_MAX:", STDIN_FILENO, _PC_NAME_MAX);
	fpathconfPrint("_PC_PATH_MAX:", STDIN_FILENO, _PC_PATH_MAX);
	fpathconfPrint("_PC_PIPE_BUF:", STDIN_FILENO, _PC_PIPE_BUF);
	exit(EXIT_SUCCESS);
}
