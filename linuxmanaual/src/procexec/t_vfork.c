#include "../lib/tlpi_hdr.h"

int main(int argc,char *argv[])
{
  int istack=222;

  switch(vfork()){
  case -1:
    errExit("vfork");
  case 0:
    sleep(3);			/* Child executes first,in parent's memory space 
				   Event if we sleep for a while,parent still is not scheduled  */
    write(STDOUT_FILENO,"Child executing\n",16);
    istack*=3;			/* This change will be seen by parent */
    _exit(EXIT_SUCCESS);
  default:			/* Parent is blocked until child exits */
    write(STDOUT_FILENO,"Parent executing\n",17);
    printf("istack=%d\n",istack);
    exit(EXIT_SUCCESS);
  }
}
