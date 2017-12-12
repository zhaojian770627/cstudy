#include "testfs.h"

void report(char *label)
/* installboot: label: No such file or directory */
{
	fprintf(stderr, "testfs: %s: %s\n", label, strerror(errno));
}

void fatal(char *label)
{
	report(label);
	exit(1);
}
