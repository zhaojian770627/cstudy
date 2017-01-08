#include <sys/resource.h>
#include "../../lib/tlpi_hdr.h"

int main(int argc,char* argv[])
{
  struct rusage res;
  if(getrusage(RUSAGE_SELF,&res)==-1)
    errExit("getrusage");
  exit(EXIT_SUCCESS);
}
