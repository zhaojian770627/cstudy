/*
 * e1.c
 *
 *  Created on: Oct 15, 2016
 *      Author: root
 */

#include <unistd.h>
#include <limits.h>
#include "../../lib/tlpi_hdr.h"
int main(int argc, char *argv[]) {
	char path[PATH_MAX];
	getcwd(path, PATH_MAX);
	printf(path);
	exit(EXIT_SUCCESS);
}
