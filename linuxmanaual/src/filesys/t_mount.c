/*
 * t_mount.c
 *
 *  Created on: Sep 27, 2016
 *      Author: root
 */

#include <sys/mount.h>
#include "../lib/tlpi_hdr.h"

static void usageError(const char *progName, const char *msg) {
	if (msg != NULL)
		fprintf(stderr, "%s", msg);

	fprintf(stderr, "Usage:%s [options] source target\n\n", progName);
	fprintf(stderr, "Available options:\n");
#define fpe(str) fprintf(stderr,"    " str)		/* Shorter! */
	fpe("-t fstype  [e.g.,'ext2 or 'reiserfs']\n");
	fpe("-o data    [file system-dependent options,\n");
	fpe("           e.g.,'bsdgroups' for ext2\n");
	fpe("-f mountflags  can include any of:\n");
#define fpe2(str) fprintf(stderr, "                " str)
	fpe2("b - MS_BIND           create a bind mount\n");
	fpe2("d - MS_DIRSYNC        synchronous directory updates\n");
	fpe2("l - MS_MANDLOCK       permit mandatory locking\n");
	fpe2("m - MS_MOVE           atomically move subtree\n");
	fpe2("A - MS_NOATIME        don't update atime(last access time)\n");
	fpe2("V - MS_NODEV          don't permit device access\n");
	fpe2("D - MS_NODIRATIME     don't update atime on directories\n");
	fpe2("E - MS_NOEXEC         don't allow executables\n");
	fpe2("S - MS_NOSUID         disable set-user/group-ID programs\n");
	fpe2("r - MS_RDONLY         read-only mount\n");
	fpe2("c - MS_REC            recursive mount\n");
	fpe2("R - MS_REMOUNT        remount\n");
	fpe2("s - MS_SYNCHRONOUS    make writes synchronous\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
	usageError("a", "b");
}
