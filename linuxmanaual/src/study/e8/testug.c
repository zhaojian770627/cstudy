/*
 * free_and_sbrk.c
 *
 *  Created on: Sep 5, 2016
 *      Author: root
 */

#include "../../lib/tlpi_hdr.h"
#include "../../users_groups/ugid_functions.h"

int main(int argc, char *argv[]) {
	printf("%s\n", userNameFromId(0));
	printf("%d\n", userIdFromName("zj"));
	printf("%d\n", groupIdFromName("zj"));
	printf("%s\n", groupNameFromId(500));
	exit(EXIT_SUCCESS);
}
