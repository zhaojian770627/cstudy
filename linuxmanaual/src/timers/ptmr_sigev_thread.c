#include <signal.h>
#include <time.h>
#include <pthread.h>
#include "../time/curr_time.h"
#include "../lib/tlpi_hdr.h"
#include "itimerspec_from_str.h"

static pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond=PTHREAD_COND_INITIALIZER;

static int expireCnt=0;

static void threadFunc(union sigval sv){
  time_t *tidptr;
  int s;

  tidptr=sv.sival_ptr;
  printf("ThreadId is %ld\n",(long)pthread_self());
  printf("[%s] Thread notify\n",currTime("%T"));
  printf("    timer ID=%ld\n",(long)*tidptr);
  printf("    timer_getoverrun()=%ld\n",timer_getoverrun(*tidptr));

  /* Increment counter variable shared with main thread and signal
     condition variable to notify main thread of the change. */
  s=pthread_mutex_lock(&mtx);
  if(s!=0)
    errExitEN(s,"pthread_mutex_lock");
  expireCnt+=1+timer_getoverrun(*tidptr);
  s=pthread_mutex_unlock(&mtx);
  if(s!=0)
    errExitEN(s,"pthread_cond_signal");
  s=pthread_cond_signal(&cond);
  if(s!=0)
    errExitEN(s,"pthread_cond_signal");
}

int main(int argc,char *argv[])
{
  struct sigevent sev;
  struct itimerspec ts;
  timer_t *tidlist;
  int s,j;
  if(argc<2)
    usageErr("%s secs[/nsecs][:int-secs[/int-nsecs]]...\n",argv[0]);

  tidlist=calloc(argc-1,sizeof(time_t));
  if(tidlist==NULL)
    errExit("malloc");

  sev.sigev_notify=SIGEV_THREAD; /* Notify via thread */
  sev.sigev_notify_function=threadFunc; /* Thread start function */
  sev.sigev_notify_attributes=NULL;	/* Could be pointer to pthread_attr_t structure */
  /* Create and start one timer for each command-line argument */
  for(j=0;j<argc-1;j++){
    itimerspecFromStr(argv[j+1],&ts);
    sev.sigev_value.sival_ptr=&tidlist[j]; /* Passed as argument to threadFunc */
    if(timer_create(CLOCK_REALTIME,&sev,&tidlist[j])==-1)
      errExit("time_create");
    printf("Time ID:%ld (%s)\n",(long)tidlist[j],argv[j+1]);
    if(timer_settime(tidlist[j],0,&ts,NULL)==-1)
      errExit("timer_settime");
  }
  /* The main thread waits on a condition variable that is signaled
   on each invocation of the thread notification functin.We
   Print message so that the user can see that this occurred.*/
  s=pthread_mutex_lock(&mtx);
  if(s!=0)
    errExitEN(s,"pthread_mutex_lock");

  for(;;){
    s=pthread_cond_wait(&cond,&mtx);
    if(s!=0)
      errExitEN(s,"pthread_cond_wait");
    printf("main():expireCnt=%d\n",expireCnt);
  }
  exit(EXIT_SUCCESS);
}
