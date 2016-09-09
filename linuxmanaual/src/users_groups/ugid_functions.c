/*
 * ugid_functions.c
 *
 *  Created on: Sep 9, 2016
 *      Author: root
 */

#include <pwd.h>
#include <grp.h>
#include <ctype.h>
#include "ugid_functions.h"

char * /* Return name corresponding to 'uid'. or NULL on error*/
userNameFromId(uid_t uid) {
	struct passwd *pwd;
	pwd = getpwuid(uid);
	return (pwd == NULL) ? NULL : pwd->pw_name;
}

uid_t /* Return UID corresponding to 'name',or -1 on error */
userIdFromName(const char *name) {
	struct passwd *pwd;
	uid_t u;
	char *endptr;
	if (name == NULL || *name == '\0')	// On NULL or empty string
		return -1;						// return an error
	u = strtol(name, &endptr, 10);	// As a convenience to caller
	if (*endptr == '\0')
		return u;
	pwd = getpwnam(name);
	if (pwd == NULL)
		return -1;
	return pwd->pw_uid;
}

char * /* Return name corresponding to 'gid'. or NULL on error*/
groupNameFromId(uid_t gid) {
	struct group *grp;
	grp = getgrgid(gid);
	return (grp == NULL) ? NULL : grp->gr_name;
}

gid_t /* Return GID corresponding to 'name',or -1 on error */
groupIdFromName(const char *name) {
	struct group *grp;
	uid_t u;
	char *endptr;
	if (name == NULL || *name == '\0')	// On NULL or empty string
		return -1;						// return an error
	u = strtol(name, &endptr, 10);	// As a convenience to caller
	if (*endptr == '\0')
		return u;
	grp = getgrnam(name);
	if (grp == NULL)
		return -1;
	return grp->gr_gid;
}
