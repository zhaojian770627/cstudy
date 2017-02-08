#include "../svsem/semun.h"		/* Definition of semun union */
#include "svshm_xfr.h"

int main(int argc,char *argv[])
{
  int semid,shmid,bytes,xfrs;
  struct shmseg *shmp;

  /* Get IDs for semaphore set and shared memory created by 
     writer*/
  semid=semget(SEM_KEY,0,0);
  if(semid==-1)
    errExit("segment");

  shmid=shmget(SHM_KEY,0,0);
  if(shmid==-1)
    errExit("shmget");

  shmp=shmat(shmid,NULL,SHM_RDONLY);
  if(shmp==(void*)-1)
    errExit("shmat");

  /* Transfer blocks of data from from shared memory to stdout */
  for(xfrs=0,bytes=0;;xfrs++){
    if(reserveSem(semid,READ_SEM)==-1) /* Wait for our turn */
      errExit("reserveSem");

    if(shmp->cnt==0)
      break;

    bytes+=shmp->cnt;
    if(write(STDOUT_FILENO,shmp->buf,shmp->cnt)!=shmp->cnt)
      fatal("partial/failed write");

    if(releaseSem(semid,WRITE_SEM)==-1) /* Give writer a turn */
      errExit("releaseSem");
  }

  /* Give writer one one more turn,so it can clean up */
  if(releaseSem(semid,WRITE_SEM)==-1)
    errExit("reserveSem");

  fprintf(stderr,"Received %d bytes (%d xfrs)\n",bytes,xfrs);
  exit(EXIT_SUCCESS);
}
