#include <sys/time.h>
#include <sys/select.h>
#include "../lib/tlpi_hdr.h"

static void
usageError(const char *progName)
{
  fprintf(stderr,"Usage:%s {timeout|-} fd-num[rw]...\n",progName);
  fprintf(stderr,"    -means infinite timeout;\n");
  fprintf(stderr,"    r=monitor for read\n");
  fprintf(stderr,"    w=monitor for write\n\n");
  fprintf(stderr,"    e.g.:%s - Orw 1w\n",progName);
  exit(EXIT_FAILURE);
}

