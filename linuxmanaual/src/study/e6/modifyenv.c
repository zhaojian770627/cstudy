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

int M_setenv(const char *name, const char *value, int overwrite) {
	strcpy(env, name);
	strcat(env, "=");
	strcat(env, value);

	if (getenv(name) != NULL && overwrite == 0)
		return 0;
	if (putenv(env) == 0)
		return 0;
	else
		return -1;
}

int main(int argc, char *argv[]) {
	int j;
	char **ep;

	clearenv(); /** Erase entire environment */

	M_setenv("TEST1", "123456890A", 0);
	M_setenv("TEST2", "123456890B", 0);

	//env[9] = 'A';
	for (ep = environ; *ep != NULL; ep++)
		puts(*ep);

	exit(EXIT_SUCCESS);
}
