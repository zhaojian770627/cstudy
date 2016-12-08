#include <signal.h>
#include <sys/wait.h>
#include "print_wait_status.h"
#include "../time/curr_time.h"
#include "../lib/tlpi_hdr.h"

static volatile int numLiveChildren=0; /* Number of children started 
					but not yet waited on*/
static void sigchldHandler(int sig)
{
  int status,savedErrno;
  pid_t childPid;

  /* UNSAFE:This handler uses non-async-signal-safe functions
     (printf(),printWaitStatus(),currTime();see Section 21.1.2*/

  savedErrno=errno;		/* In casee we modify 'errno' */
  printf("%s handler:Caught SIGCHLD\n",currTime("%T"));

  while((childPid=waitpid(-1,&status,WNOHANG))>0){
    printf("%s handler:Reaped chhild %ld - ",currTime("%T"),
	   (long)childPid);
    printWaitStatus(NULL,status);
    numLiveChildren--;
  }
  if(childPid==-1 && errno!=ECHILD)
    errMsg("waitpid");
  sleep(5);			/* Artificially lengthen execution of 
				   handler*/
  printf("%s handler: returning\n",currTime("%T"));
  errno=savedErrno;
}

int main(int argc,char *argv[])
{
  int j,sigCnt;
  sigset_t blockMask,emptyMask;
  struct sigaction sa;

  if(argc<2||strcmp(argv[1],"--help")==0)
    usageErr("%s child-sleep-time...\n",argv[0]);

  setbuf(stdout,NULL);		/* Disable buffering of stdout */

  sigCnt=0;
  numLiveChildren=argc-1;

  sigemptyset(&sa.sa_mask);
  sa.sa_flags=0;
  sa.sa_handler=sigchldHandler;
  if(sigaction(SIGCHLD,&sa,NULL)==-1)
    errExit("sigaction");
  /* Block SIGCHLD to prevent its delivery if a child terminates
     before the parent commences the sigsuspend() loop below */
  sigemptyset(&blockMask);
  sigaddset(&blockMask,SIGCHLD);
  if(sigprocmask(SIG_SETMASK,&blockMask,NULL)==-1)
    errExit("sigprocmask");

  for(j=1;j<argc;j++){
    switch(fork()){
    case -1:
      errExit("fork");
    case 0:			/* Child - sleeps and the exits */
      sleep(getInt(argv[j],GN_NONNEG,"child-sleep-time"));
      printf("%s Child %d (PID=%ld) exiting\n",currTime("%T"),
	     j,(long)getpid());
      _exit(EXIT_SUCCESS);
    default:			/* Parent - loops to create next child */
      break;
    }
  }
  /* Parent comes here:wait for SIGCHLD until all children are dead */
  sigemptyset(&emptyMask);
  while(numLiveChildren>0){
    if(sigsuspend(&emptyMask)==-1 && errno!=EINTR)
      errExit("sigsuspend");
    sigCnt++;
  }
  printf("%s All %d children have terminated; SIGCHLD was caught "
	 "%d times \n",currTime("%T"),argc-1,sigCnt);
  exit(EXIT_SUCCESS);
}