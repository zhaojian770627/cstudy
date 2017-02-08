#include "../svsem/semun.h"		/* Definition of semun union */
#include "svshm_xfr.h"

int main(int argc,char *argv[])
{
  int semid,shmid,bytes,xfrs;
  struct shmseg *shmp;
  union semun dummy;

  semid=semget(SEM_KEY,2,IPC_CREAT|OBJ_PERMS);
  if(semid==-1)
    errExit("segment");

  if(initSemAvailable(semid,WRITE_SEM)==-1)
    errExit("initSemAvailable");

  if(initSemInUse(semid,READ_SEM)==-1)
    errExit("initSemInUse");

  shmid=shmget(SHM_KEY,sizeof(struct shmseg),IPC_CREAT|OBJ_PERMS);
  if(shmid==-1)
    errExit("shmget");

  shmp=shmat(shmid,NULL,0);
  if(shmp==(void*)-1)
    errExit("shmat");

  /* Transfer blocks of data from stdin to shared memory */

}
