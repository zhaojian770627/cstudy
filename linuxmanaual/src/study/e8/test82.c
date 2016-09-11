/*
 * test82.c
 *
 *  Created on: Sep 11, 2016
 *      Author: root
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pwd.h>
#include "../../lib/tlpi_hdr.h"

struct passwd * M_getpwnam(const char *name) {
	struct passwd *pwd;
	while ((pwd = getpwent()) != NULL) {
		if (strcmp(name, pwd->pw_name) == 0) {
			return pwd;
		}
	}
	endpwent();
	return NULL;
}

int main(int argc, char *argv[]) {
	int i;
	struct passwd *pwd;
	if (argc < 2 || strcmp(argv[1], "--help") == 0)
		usageErr("%s <username> \n", argv[0]);

	for (i = 1; i < argc; ++i) {
		pwd = M_getpwnam(argv[i]);
		if (pwd != NULL)
			printf("%s find, uid is %d \n", argv[i], pwd->pw_uid);
		else
			printf("%s not find uid \n", argv[i]);
	}
	exit(EXIT_SUCCESS);
}

