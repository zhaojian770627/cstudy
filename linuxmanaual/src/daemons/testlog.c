
#include "become_daemon.h"
#include <syslog.h>
#include "../lib/tlpi_hdr.h"

int
main(int argc, char *argv[])
{
  char buf[]="test";
  int count=0;
  //becomeDaemon(0);
  alarm(60);

  openlog(buf,LOG_PID|LOG_CONS|LOG_NOWAIT,LOG_LOCAL0);
  for(;;)
    {
      syslog(LOG_WARNING,"Warning:%d",count);
      count++;
      sleep(1);
    }

  exit(EXIT_SUCCESS);
}
