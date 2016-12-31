#define _GNU_SOURCE 		
#include <string.h>
#include <signal.h>
#include "../lib/tlpi_hdr.h"

static void handler(int sig)	/* Signal handler */
{
  printf("PID=%ld: caught signal %d (%s)\n",(long)getpid(),
	 sig,strsignal(sig));
}

int main(int argc,char *argv[])
{
  int j;
  struct sigaction sa;
  if(argc<2||strcmp(argv[1],"--help")==0)
    usageErr("%s {s|p} ...\n",argv[0]);

  setbuf(stdout,NULL);		/* Make stdout unbufferred */

  sigemptyset(&sa.sa_mask);
  sa.sa_flags=0;
  sa.sa_handler=handler;
  if(sigaction(SIGHUP,&sa,NULL)==-1)
    errExit("sigaction");
  if(sigaction(SIGCONT,&sa,NULL)==-1)
    errExit("sigaction");
  printf("parent:PID=%ld,PPID=%ld,PGID=%ld,SID=%ld\n",
	 (long)getpid(),(long)getppid(),
	 (long)getpgrp(),(long)getsid(0));

  /* Create one child for each command-line argument */
  for(j=1;j<argc;j++){
    switch(fork()){
    case -1:
      errExit("fork");
    case 0:			/* Child */
      printf("child:PID=%ld,PPID=%ld,PGID=%ld,SID=%ld\n",
	     (long)getpid(),(long)getppid(),
	     (long)getpgrp(),(long)getsid(0));
      if(argv[j][0]=='s'){		/* Stop via signal */
	printf("PID=%ld stopping\n",(long)getpid());
	raise(SIGSTOP);
      }else{			/* Wait for signal */
	alarm(60);			/* So we die if not SIGHUPed */
	printf("PID=%ld pausing\n",(long)getpid());
	pause();
      }
      _exit(EXIT_SUCCESS);
    default:			/* parent carries on round loop */
      break;
    }
  }
  /* Parent falls through to here after creating all children */
  sleep(3);			/* Give children a chance to start */
  printf("parent exiting\n");
  exit(EXIT_SUCCESS);		/* And orphan them and their group */
}
