/*
 * acl_view.c
 *
 *  Created on: Oct 9, 2016
 *      Author: root
 */
#include <acl/libacl.h>

#include "../lib/tlpi_hdr.h"

static void usageError(char *progName) {
	fprintf(stderr, "Usage:%s [-d] filename\n", progName);
	exit(EXIT_FAILURE);
}
int main(int argc, char *argv[]) {
	acl_t acl;
	acl_type_t type;
	acl_entry_t entry;
	acl_tag_t tag;

	uid_t *uidp;
	gid_t *gidp;
	acl_permset_t permset;
	char *name;
	int entryId, permVal, opt;

	type = ACL_TYPE_ACCESS;

	while ((opt = getopt(argc, argv, "d")) != -1) {
		switch (opt) {
		case 'd':
			type = ACL_TYPE_DEFAULT;
			break;
		case '?':
			usageError(argv[0]);
		}
	}

	exit(EXIT_SUCCESS);
}
