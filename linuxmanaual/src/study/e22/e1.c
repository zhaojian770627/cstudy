#define _GNU_SOURCE
#include <string.h>
#include <signal.h>
#include "../../lib/tlpi_hdr.h"

static volatile int handlerSleepTime;

/* Handler for signals established using SIGCONT */
static void handler(int sig)
{
  printf("Begin SIGCONT");
}

int main(int argc,char *argv[])
{
  struct sigaction sa;
  int sig,count;
  sigset_t prevMask,blockMask;
  if(argc<2 || strcmp(argv[1],"--help")==0)
    usageErr("%s:times",argv[0],(long)getpid());
  printf("%s:PID is %ld\n",argv[0],(long)getpid());
  handlerSleepTime=(argc>1)?getInt(argv[1],GN_NONNEG,"handler-sleep_time"):1;

  /* Establish handler for most signals.During execution of the handler,
     mask all other signals to prevent handlers recursively interrupting
     each other(which would make the output hard to read).*/
  sa.sa_sigaction=handler;
  sa.sa_flags=0;
  sigemptyset(&sa.sa_mask);

  sigemptyset(&blockMask);
  sigaddset(&blockMask,SIGCONT);

  sigaction(SIGCONT,&sa,NULL);

  /* Optionally block signals and sleep,allowing signals to be
     send to us before they are unblocked and handled */

  if(sigprocmask(SIG_SETMASK,&blockMask,&prevMask)==-1)
    errExit("sigprocmask");
  printf("%s:signal blocked-sleeping %s seconds\n",argv[0],argv[1]);
  for(count=0;count<handlerSleepTime;count++)
    {
      printf("%d times\r",count);
      fflush(stdout);
      sleep(1);
    }
  printf("%s:sleep complete\n",argv[0]);
  if(sigprocmask(SIG_SETMASK,&prevMask,NULL)==-1)
    errExit("sigprocmask");

  exit(EXIT_SUCCESS);
}
