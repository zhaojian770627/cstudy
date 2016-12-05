#define _GNU_SOURCE
#include <string.h>
#include <sys/wait>
#include "print_wait_status.h"
#include "../lib/tlpi_hdr.h"

void printWaitStatus(cont char *msg,int status)
{
  if(msg!=NULL)
    printf("%s",msg);
  if(WIFEXITED(status)){
    printf("child exited,status=%d\n",WEXITSTATUS(status));
  }
  else if(WIFSIGNALED(status)){
    printf("child killed by signal %d (%s)",
	   WTERMSIG(status),strsignal(WTERMSIG(status)));
#ifdef WCOREDUMP
    if(WCOREDUMP(status))
      printf("(core dumped)");
#endif
    printf("\n");
  }else if(WIFSTOPPED(status)){
    printf("child stopped by signal %d (%s)\n",
	   WSTOPSIG(status),strsignal(WSTOPSIG(status)));
#ifdef WIFCONTINUED 	/* SUSv3 has this,but older Linux versions
			   and some other UNIX implementations don't */
  }else if(WIFCONTINUED(status)){
    printf("child continued\n");
#endif
  }else{			/* Should never happen */
    printf("what happended to this child?(status=%x)\n",
	   (unsigned int)status);
  }
}
