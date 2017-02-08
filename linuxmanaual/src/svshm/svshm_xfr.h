#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "../svsem/binary_sems.h"
#include "../lib/tlpi_hdr.h"

#define SHM_KEY 0x1234		/* Key for shared memory segment */
#define SEM_KEY 0x5678		/* Key for semaphore set */

/* Permissions for our objects */
#define OBJ_PERMS (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP)

#define WRITE_SEM 0		/* Writer has access to shared memory */
#define READ_SEM 1		/* Reader has access to shared memory */

#ifndef BUF_SIZE		/* Allow "cc -D" to override definition */
#define BUF_SIZE 1024		/* Size of transfer buffer */
#endif

struct shmseg{			/* Defines structure of shared memory segment */
  int cnt;			/* Number of bytes used in 'buf' */
  char buf[BUF_SIZE];		/* Data being transferred */
};
