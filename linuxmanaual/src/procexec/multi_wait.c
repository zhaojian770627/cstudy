#include <sys/wait.h>
#include <time.h>
#include "../time/curr_time.h"
#include "../lib/tlpi_hdr.h"

int main(int argc,char *argv[])
{
  int numDead;			/* Number of children so far waited fore */
  pid_t childPid;		/* PID of waited for chid */
  int j;

  if(argc<2||strcmp(argv[1],"--help")==0)
    usageErr("%s sleep-time...\n",argv[0]);
  
  setbuf(stdout,NULL);		/* Disable buffering of stdout */
  for(j=1;j<argc;j++){		/* Create one chid for each argument */
    switch(fork()){
    case -1:
      errExit("fork");
    case 0:			/* Child sleeps for a whiile thenexits */
      printf("[%s] child %d started with PID %ld,sleeping %s "
	     "seconds\n",currTime("%T"),j,(long)getpid(),argv[j]);
      sleep(getInt(argv[j],GN_NONNEG,"sleep-time"));
      _exit(EXIT_SUCCESS);
    default:			/* Parent just continues around loop */
      break;
    }
  }
  numDead=0;
  for(;;){			/* Parent waits for each child to exit */
    childPid=wait(NULL);
    if(childPid==-1){
      if(errno==ECHILD){
	printf("No more children - bye!\n");
	exit(EXIT_SUCCESS);
      }
      else{			/* Some other (unexpected) error */
	errExit("wait");
      }
    }
    numDead++;
    printf("[%s] wait() returned child PID %ld (numDead=%d)\n",
	   currTime("%T"),(long)childPid,numDead);
  }
}
