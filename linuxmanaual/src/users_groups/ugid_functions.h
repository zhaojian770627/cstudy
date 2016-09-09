/*
 * ugid_functions.h
 *
 *  Created on: Sep 9, 2016
 *      Author: root
 */

#ifndef UGID_FUNCTIONS_H
#define UGID_FUNCTIONS_H

#include "../lib/tlpi_hdr.h"

char *userNameFromId(uid_t uid);

uid_t userIdFromName(const char *name);

char *groupNameFromId(gid_t gid);

gid_t groupIdFromName(const char *name);

#endif /* USERS_GROUPS_UGID_FUNCTIONS_H_ */
