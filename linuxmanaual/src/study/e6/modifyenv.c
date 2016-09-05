/*
 * modifyenv.c
 *
 *  Created on: Sep 5, 2016
 *      Author: root
 */

#define _GNU_SOURCE

#include <stdlib.h>
#include <string.h>
#include "../../lib/tlpi_hdr.h"

extern char **environ;
char env[1000];
char *pos = env;

int M_setenv(const char *name, const char *value, int overwrite) {
	char tmp[100];

	strcpy(tmp, name);
	strcat(tmp, "=");
	strcat(tmp, value);

	size_t length = strlen(tmp);

	strcpy(pos, tmp);

	if (getenv(name) != NULL && overwrite == 0)
		return 0;
	if (putenv(pos) == 0) {
		pos += length + 1;
		return 0;
	} else
		return -1;
}

int M_unsetenv(const char *name) {
	if (putenv((char*) name) == 0)
		return 0;
	return -1;

}

int main(int argc, char *argv[]) {
	int j;
	char **ep;

	clearenv(); /** Erase entire environment */

	for (j = 1; j < argc; j++)
		if (putenv(argv[j]) != 0)
			errExit("putenv:%s", argv[j]);

	if (M_setenv("GREET", "Hello world", 0) == -1)
		errExit("M_setenv");

	M_unsetenv("BYE");
	for (ep = environ; *ep != NULL; ep++)
		puts(*ep);

	exit(EXIT_SUCCESS);
}
