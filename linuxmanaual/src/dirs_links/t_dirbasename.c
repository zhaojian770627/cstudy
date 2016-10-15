/*
 * t_dirbasename.c
 *
 *  Created on: Oct 15, 2016
 *      Author: root
 */

#include <libgen.h>
#include "../lib/tlpi_hdr.h"

int main(int argc, char **argv) {
	char *t1, *t2;
	int j;
	for (j = 0; j < argc; j++) {
		t1 = strdup(argv[j]);
		if (t1 == NULL)
			errExit("strdup");
		t2 = strdup(argv[j]);
		if (t2 == NULL)
			errExit("strdup");

		printf("%s ==> %s +%s\n", argv[j], dirname(t1), basename(t2));
		free(t1);
		free(t2);
	}
	exit(EXIT_SUCCESS);
}

