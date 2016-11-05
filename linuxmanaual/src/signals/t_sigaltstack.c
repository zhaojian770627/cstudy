#define _GNU_SOURCE
#include <string.h>
# include <signal.h>
#include "../lib/tlip_hdr.h"

static void
sigsegvHandler(int sig)
{
  int x;
  /* UNSAFE:this handler uses non-async-signal-safe functions  */
  /* (printf(),strsignal(),fflush; */
  printf("Caught signal %d (%s)\n",sig,strsignal(sig));
  printf("Top of handler stack near    %10p\n",(void*)&x);
  fflush(NULL);
  _exit(EXIT_FAILURE);		/* Can't return after SIGSEGV */
}

static void overflowStack(int callNum) /* A recursive function that overflows the stack */
{
  char a[100000];		/* Make this stack frame large */
  printf("Call %4d- top of stack near %10p\n",callNum,&a[0]);
  overflowStack(callNum+1);
}
int main(int argc,char *argv[])
{

}
