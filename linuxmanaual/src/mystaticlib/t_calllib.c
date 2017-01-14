#include "../lib/tlpi_hdr.h"

int main(int argc,char *argv[])
{
  int i;
  i=getInt("1000",GN_GT_0,"test");
  printf("%d\n",i);
  exit(EXIT_SUCCESS);
}
