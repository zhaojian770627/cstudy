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

}
