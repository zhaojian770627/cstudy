#include <sys/wait.h>
#include "../lib/tlpi_hdr.h"

#define BUF_SIZE 10

int main(int argc, char *argv[])
{
  int pfd[2];			/* Pipe file descriptors */
  char buf[BUF_SIZE];

  if(pipe(pfd)==-1)		/* Create the pipe */
    errExit("pipe");

  switch(fork()){
  case -1:
    errExit("fork");
  case 0:			/* First child:exec 'ls' to write to pipe */
    if(close(pfd[0])==-1)	/* Write read is unused */
      errExit("close - 1");

    /* Duplicate stdout on write end of pipe;close duplicated 
       descriptor */
    if(pfd[1]!=STDOUT_FILENO){	/* Defensive check */
      if(dup2(pfd[1],STDOUT_FILENO)==-1)
	errExit("dup2 1");
      if(close(pfd[1])==-1)
	errExit("close 2");
    }
    execlp("ls","ls",(char *)NULL); /* Writes to pipe */
    errExit("execlp ls");
  default:			/* Parent falls through to create next child */
    break;
  }

  switch(fork()){
  case -1:
    errExit("fork");
  case 0:			/* second:exec 'wc' to read from pipe */
    if(close(pfd[1])==-1)	/* Write read is unused */
      errExit("close - 3");

    /* Duplicate stdin on read end of pipe;close duplicated 
       descriptor */
    if(pfd[0]!=STDIN_FILENO){	/* Defensive check */
      if(dup2(pfd[0],STDIN_FILENO)==-1)
	errExit("dup2 2");
      if(close(pfd[0])==-1)
	errExit("close 4");
    }
    execlp("wc","wc","-l",(char *)NULL); /* Reads to pipe */
    errExit("execlp ls");
  default:			/* Parent falls through */
    break;
  }

  /* Parent closes unused file descriptors for pipe,and waits for
   children */
  if(close(pfd[0])==-1)
    errExit("close 5");
  if(close(pfd[1])==-1)
    errExit("close 6");
  if(wait(NULL)==-1)
    errExit("wait 1");
  if(wait(NULL)==-1)
    errExit("wait 2");

  exit(EXIT_SUCCESS);
}
