#include <stdio.h>
#include "../lib/tlpi_hdr.h"
#include "create_pid_file.h"

int main(int argc,char* argv[])
{
  if(createPidFile("t_runone","./t_runone.pid",0)==-1)
    errExit("createPidFile");

  sleep(60);
  if( remove("./t_runone.pid")==-1)
    errExit("remove");

  exit(EXIT_SUCCESS);
}
