/*
 * free_and_sbrk.c
 *
 *  Created on: Sep 5, 2016
 *      Author: root
 */

#include <unistd.h>
#include "../../lib/tlpi_hdr.h"

int main(int argc, char *argv[]) {
	uid_t id=geteuid();
	printf("%d\n",id);
	exit(EXIT_SUCCESS);
}
