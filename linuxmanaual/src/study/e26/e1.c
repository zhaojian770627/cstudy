#include <signal.h>
#include <libgen.h>		/* For basename() declaration */
#include "../../lib/tlpi_hdr.h"

#define CMD_SIZE 100

int main(int argc,char *argv[])
{
  char cmd[CMD_SIZE];
  pid_t childPid;

  setbuf(stdout,NULL);		/* Disable buffering of stdout */
  printf("Parent PID=%ld\n",(long)getpid());
  switch(childPid=fork()){
  case -1:
    errExit("fork");
  case 0:			/* Child:immediately exits to become zombie */
    printf("Child (PID=%ld) exiting\n",(long)getpid());
    sleep(10);
    printf("Parent PID=%ld\n",(long)getppid());
    _exit(EXIT_SUCCESS);
  default:			/* Parent */
    exit(EXIT_SUCCESS);
  }
}
