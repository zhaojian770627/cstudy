#include <termios.h>
#include <ctype.h>
#include "../lib/tlpi_hdr.h"

int
main(int argc,char *argv[])
{
  struct termios tp;
  int intrChar;

  if(argc>1 && strcmp(argv[1],"--help")==0)
    usageErr("%s [intr-char]\n",argv[0]);

  /* Determine new INTR setting from command line */
  if(argc==1){			/* Disable */
    intrChar=fpathconf(STDIN_FILENO,_PC_VDISABLE);
    if(intrChar==-1)
      errExit("Couldn't detemine VDISABLE");
  }else if(isdigit((unsigned char)argv[1][0])){
    intrChar=strtoul(argv[1],NULL,0); /* Allow hex,octal */
  }else{			     /* Literal character */
    intrChar=argv[1][0];
  }

  /* Fetch current termianl settings,modify INTR character,and
   push changes back to the terminal driver*/
  if(tcgetattr(STDIN_FILENO,&tp)==-1)
    errExit("tcgetattr");
  tp.c_cc[VINTR]=intrChar;
  if(tcsetattr(STDIN_FILENO,TCSAFLUSH,&tp)==-1)
    errExit("tcgetattr");

  exit(EXIT_SUCCESS);
}
