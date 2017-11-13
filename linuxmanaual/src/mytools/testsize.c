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
  printf("Elf64_Addr size: %ld\n",sizeof(Elf64_Addr));
  printf("Elf64_Half size: %ld\n",sizeof(Elf64_Half));
  printf("Elf64_Off size: %ld\n",sizeof(Elf64_Off));
  printf("Elf64_Sword size: %ld\n",sizeof(Elf64_Sword));
  printf("Elf64_Word size: %ld\n",sizeof(Elf64_Word));
  exit(EXIT_SUCCESS);
}
