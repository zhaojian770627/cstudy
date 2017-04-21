#include <stdio.h>
#include "CRB.h"
#include "MEM.h"

int
main(int argc,char *argv[])
{
  CRB_Interpreter *interpreter;

  if(argc!=2){
    fprintf(stderr,"usage:%s filename",argv[0]);
    exit(1);
  }
  return 0;
}
