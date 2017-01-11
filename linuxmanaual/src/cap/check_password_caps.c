#define _BSD_SOURCE 		/* Get getpass() declareation from <unsistd.h */
#define _XOPEN_SOURCE		/* Get crypt() declaration from <unistd.h */
#include <linux/capability.h>
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
  if(caps==NULL)
    return -1;

  /* Change setting of 'capability' in the effective set of 'caps'. The
     third argument,1,is the number of items in the array 'capList'*/
  capList[0]=capability;

  if(cap_set_flag(caps.CAP_EFFECTIVE,1,capList,setting)==-1){
    cap_free(caps);
    return -1;
  }

  /* Push modified capability sets back to kernel,to change
     caller's capabilities*/

  if(cap_set_proc(caps)==-1){
    cap_free(caps);
    return -1;
  }

  /* Free the structure that was allocated  */
  if(cap_free(caps)==-1)
    return -1;

  return 0;
}

/* Raise capability in caller's effective set */
static int raiseCap(int capability)
{
  return modify(capability,CAP_SET);
}


static int dropAllCaps(void)
