#define _BSD_SOURCE		/* Get on_exit() declaration from <stdlib.h */
#include <stdlib.h>
#include "../lib/tlpi_hdr.h"

static void atexitFunc1(void)
{
  printf("atexit function 1 called\n");
}

static void atexitFunc2(void)
{
  printf("atexit function 2 called\n");
}

static void onexitFunc(int exitStatus,void *arg)
{
  printf("on_exit function called:status=%d,arg=%ld\n",exitStatus,(long)arg);
}

int main(int argc,char *argv[])
{
  exit(EXIT_SUCCESS);
}
