/*
 * free_and_sbrk.c
 *
 *  Created on: Sep 5, 2016
 *      Author: root
 */

#include "../../lib/tlpi_hdr.h"

#define MAX_ALLOCS 1000000

int main(int argc, char *argv[]) {
	void *p;
	printf("initial program break:       %10p\n", sbrk(0));
	p = malloc(1000);
	printf("p:       %10p\n", p);
	printf("initial program break:       %10p\n", sbrk(0));
	exit(EXIT_SUCCESS);
}
