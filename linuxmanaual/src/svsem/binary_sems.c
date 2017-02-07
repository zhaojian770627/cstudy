#include <sys/types.h>
#include <sys/sem.h>
#include "semun.h"
#include "binary_sems.h"

/* Variables controlling operation of functions below */

Boolean bsUseSemUndo=FALSE;	/* Use SEM_UNDO during semop()? */
Boolean bsRetryOnEintr=TRUE;	/* Retry if semop() interrupted by
				 signal handler?*/
/* Initialize semaphore to 1 (i.e.,"available") */
int initSemAvailable(int semId,int semNum)
{
  union semun arg;
  arg.val=1;
  return semctl(semId,semNum,SETVAL,arg);
}
/* Initialize semaphore to 0 (i.e.,"available") */
int initSemInUse(int semId,int semNum)
{
  union semun arg;
  arg.val=0;
  return semctl(semId,semNum,SETVAL,arg);
}

/* Reserve semaphore(blocking),return 0 on success,or -1 with 'errno'
 set to EINTR if operation was interrupted by a signal handler
 Reserve semaphore - decrement it by 1*/
int reserveSem(int semId,int semNum)
{
  struct sembuf sops;

  sops.sem_num=semNum;
  sops.sem_op=-1;
  sops.sem_flg=bsUseSemUndo?SEM_UNDO:0;

  while(semop(semId,&sops,1)==-1)
    if(errno!=EINTR||!bsRetryOnEintr)
      return -1;
  return 0;
}

/* Release semaphore - increment it by 1 */
int releaseSem(int semId,int semNum)
{
  struct sembuf sops;

  sops.sem_num=semNum;
  sops.sem_op=1;
  sops.sem_flg=bsUseSemUndo?SEM_UNDO:0;

  return semop(semId,&sops,1);
}
