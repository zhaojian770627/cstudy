#include <fcntl.h>
#include <sys/mman.h>
#include "../lib/tlpi_hdr.h"

int main(int argc,char *argv[])
{
  if(argc!=2||strcmp(argv[1],"--help")==0)
    usageErr("%s shm-name\n",argv[0]);

  if(shm_unlink(argv[1])==-1)
    errExit("shm_unlink");

  exit(EXIT_SUCCESS);
}
