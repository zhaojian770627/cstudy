#include <sys/wait.h>
#include "print_wait_status.h"
#include "../lib/tlpi_hdr.h"

int main(int argc,char *argv[])
{
  int status;
  pid_t childPid;
  if(argc>1 && strcmp(argv[1],"--help")==0)
    usageErr("%s [exit-status]\n",argv[0]);
  switch(fork()){
  case -1:exitExit("fork");
  case 0:			/* Child:either exits immediately with
				 given status or loops waiting for signals*/
    printf("Child started with PID=%ld\n",(long)getpid());
    if(argc>1)			/* Status supplied on command line? */
      exit(getInt(argv[1],0,"exit-status"));
    else
      for(;;)
	pause();
    exit(EXIT_FAILURE);		/* Not reached,but good practice */
  default:
    for(;;){
      childPid=waitpid(-1,&status,WUNTRACED
