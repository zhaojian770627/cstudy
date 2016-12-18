#include <sys/wait.h>
#include <time.h>
#include "../../time/curr_time.h"
#include "../../lib/tlpi_hdr.h"

int main(int argc,char *argv[])
{
  pid_t childPid;		/* PID of waited for chid */
  int j,num;

  if(argc!=2||strcmp(argv[1],"--help")==0)
    usageErr("%s excute num\n",argv[0]);

  num=getInt(argv[1],GN_NONNEG,"num");

  for(j=1;j<num;j++){		/* Create one chid for each argument */
    switch(vfork()){
    case -1:
      errExit("fork");
    case 0:			/* Child sleeps for a whiile thenexits */
      _exit(EXIT_SUCCESS);
    default:			/* Parent just continues around loop */
      break;
    }

    childPid=wait(NULL);
    if(childPid==-1){
      if(errno!=ECHILD){
	errExit("wait");
      }
    }
  }
}
