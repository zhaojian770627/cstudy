/*
 * test81.c
 *
 *  Created on: Sep 11, 2016
 *      Author: root
 */

#include <stdlib.h>
#include <stdio.h>
#include <pwd.h>

int main(int argc, char *argv[]) {
	printf("%s %s\n", getpwuid(0)->pw_name, getpwuid(500)->pw_name);
	printf("%s\n", getpwuid(0)->pw_name);
	printf("%s\n", getpwuid(500)->pw_name);
	exit(EXIT_SUCCESS);
}
