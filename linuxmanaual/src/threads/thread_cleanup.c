#include <pthread.h>
#include "../lib/tlpi_hdr.h"

static pthread_cond_t cond=PTHREAD_COND_INITIALIZER;
static pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
static int glob=0;		/* Predicate variable */

static void cleanupHandler(void *arg) /* Free memory pointed to by 'arg' 
				       and unlock mutex*/
{
  int s;
  printf("cleanup: freeing block at %p\n",arg);
  free(arg);
  printf("cleanup:unlocking mutex\n");
  s=pthread_mutex_unlock(&mtx);
  if(s!=0)
    errExitEN(s,"pthread_mutex_unlock");
}


static void* threadFunc(void *arg) /* Start function for thread */
{ 
  int s;
  void *buf=NULL;		/* Buffer allocated by thread */
  buf=malloc(0x10000);		/* Not a cancellation */
  printf("Thread:allocated memory at %p\n",buf);

  s=pthread_mutex_lock(&mtx);
  if(s!=0)
    errExitEN(s,"pthread_mutex_lock");
  pthread_cleanup_push(cleanupHandler,buf);
  while(glob==0){
    s=pthread_cond_wait(&cond,&mtx); /* A cancellation point */
    if(s!=0)
      errExitEN(s,"pthread_cond_wait");
  }

  printf("Thread:condition wait loop completed\n");
  pthread_cleanup_pop(1);	/* Executes cleanup handler */

  return NULL;
}

int main(int argc,char *argv[])
{
  pthread_t thr;
  void *res;
  int s;
  s=pthread_create(&thr,NULL,threadFunc,NULL);
  if(s!=0)
    errExitEN(s,"pthread_create");
  sleep(2);			/* Give thread a chance to get started */

  if(argc==1){			/* Cancel thread */
    printf("main:    about to cancel thread\n");
    s=pthread_cancel(thr);
    if(s!=0)
      errExitEN(s,"pthread_cancel");
  }else{			/* Signal condition variable */
    printf("main:    about to signal condition varibale\n");
    glob=1;
    s=pthread_cond_signal(&cond);
    if(s!=0)
      errExitEN(s,"pthread_cond_signal");
  }
  s=pthread_join(thr,&res);
  if(s!=0)
    errExitEN(s,"pthread_join");

  if(res==PTHREAD_CANCELED)
    printf("main:    thread was canceled\n");
  else
    printf("main:    thread terminated normally\n");

  exit(EXIT_SUCCESS);
}
