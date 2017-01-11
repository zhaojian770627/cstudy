#define _BSD_SOURCE 		/* Get getpass() declareation from <unsistd.h */
#define _XOPEN_SOURCE		/* Get crypt() declaration from <unistd.h */
#include <sys/capability.h>
#include <unistd.h>
#include <limits.h>
#include <pwd.h>
#include <shadow.h>
#include "../lib/tlpi_hdr.h"

/* Change setting of capability in caller's effective capabilities */
static int modifyCap(int capability,int setting)
{
  cap_t caps;
  cap_value_t capList[1];

  caps=cap_get_proc();
}
