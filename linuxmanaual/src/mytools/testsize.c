/*
 * e1.c
 *
 *  Created on: Sep 21, 2016
 *      Author: root
 */

#include "../lib/tlpi_hdr.h"
#include <elf.h>

#define CHARMAX 1024

int main(int argc, char *argv[]) {
  printf("Elf32_Half size  %ld\n",sizeof(Elf32_Half));
  exit(EXIT_SUCCESS);
}
