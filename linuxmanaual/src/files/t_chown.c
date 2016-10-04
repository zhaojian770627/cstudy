/*
 * t_chown.c
 *
 *  Created on: Oct 4, 2016
 *      Author: root
 */

#include <pwd.h>
#include <grp.h>
#include "../users_groups/ugid_functions.h"
#include "../lib/tlpi_hdr.h"

int main(int argc, char *argv[]) {
	uid_t uid;
	gid_t gid;
	int j;
	Boolean errFnd;

	if (argc < 3 || strcmp(argv[1], "--help") == 0)
		usageErr("%s owner group [file...]\n"
				"         owner or group can be '-',"
				"meaning leave unchanged\n", argv[0]);

	if (strcmp(argv[1], "-") == 0) {		// "-" ==> don't change owner
		uid = -1;
	} else {
		uid = userIdFromName(argv[1]);
		if (uid == -1)
			fatal("No such user (%s)", argv[1]);
	}

	if (strcmp(argv[2], "-") == 0) {		// "-" ==> don't change owner
		gid = -1;
	} else {
		gid = groupIdFromName(argv[2]);
		if (gid == -1)
			fatal("No such user (%s)", argv[2]);
	}

	errFnd = FALSE;
	for (j = 3; j < argc; j++) {
		if (chown(argv[j], uid, gid) == -1) {
			errMsg("chown:%s", argv[j]);
			errFnd = TRUE;
		}
	}
	exit(errFnd ? EXIT_FAILURE : EXIT_SUCCESS);
}
