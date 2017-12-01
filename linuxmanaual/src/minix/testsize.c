/*
 * e1.c
 *
 *  Created on: Sep 21, 2016
 *      Author: root
 */

#include "../lib/tlpi_hdr.h"
#include <elf.h>

#define CHARMAX 1024
#define SECTOR_SIZE	512	/* Disk sector size. */
#define align(n)	(((n) + ((SECTOR_SIZE) - 1)) & ~((SECTOR_SIZE) - 1))

int main(int argc, char *argv[]) {
  printf("1- %d\n",align(1));
  printf("2- %d\n",align(2));
  printf("512- %d\n",align(512));
  printf("513- %d\n",align(513));
  printf("1024- %d\n",align(1024));
  printf("1025- %d\n",align(1025));
  exit(EXIT_SUCCESS);
}
