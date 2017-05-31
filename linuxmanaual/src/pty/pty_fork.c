
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "pty_master_open.h"
#include "pty_fork.h"
#include "../lib/tlpi_hdr.h"

#define MAX_SNAME 1000

pid_t
ptyFork(int *masterFd,char *slaveName,size_t snLen,
	const struct termios *slaveTermios,const struct winsize *slaveWS)
{
  int mfd,slaveFd,savedErrno;
  pid_t childPid;
  char slname[MAX_SNAME];

  mfd=ptyMasterOpen(slname,MAX_SNAME);
  if(mfd==-1)
    return -1;

  if(slaveName!=NULL){		/* retry slave name to caller */
    if(strlen(slname)<snLen){
      strncpy(slaveName,slname,snLen);
    }else{			/* 'slaveName' was too small */
      close(mfd);
      errno=EOVERFLOW;
      return -1;
    }
  }
  childPid=fork();

  if(childPid==-1){		/* fork failed */
    savedErrno=errno;		/* close() might change 'errno' */
    close(mfd);			/* Don't leak file descriptors */
    errno=savedErrno;
    return -1;
  }

  if(childPid!=0){		/* Parent  */
    *masterFd=mfd;		/* Only parent gets master fd */
    return childPid;		/* Like parent of fork */
  }

  /* Child falls through to here */
  if(setsid()==-1)		/* Start a new session */
    err_exit("ptyFork:setsid");

  close(mfd);			/* Not needed in child */

  slaveFd=open(slname,O_RDWR);	/* Becomes controlling tty */
  if(slaveFd==-1)
    err_exit("ptyFork:open-slave");

#ifdef TIOCSCTTY		/* Acquire controlling tty on BSD */
  if(ioctl(slaveFd,TIOCSCTTY,0)==-1)
    err_exit("ptyFork:ioctl-TIOCSCTTY");
#endif

  if(slaveTermios!=NULL)		/* Set slave tty attributes */
    if(tcsetattr(slaveFd,TCSANOW,slaveTermios)==-1)
      err_exit("ptyFork:tcsetattr");

  if(slaveWS!=NULL)		/* Set slave tty window size */
    if(ioctl(slaveFd,TIOCSWINSZ,slaveWS)==-1)
      err_exit("ptyFork:ioctl-TIOCSWINSZ");

  /* Duplicate pty slave to be child's stdin,stdout,and stderr */

  if(dup2(slaveFd,STDIN_FILENO)!=STDIN_FILENO)
    err_exit("ptyFork:dup2-STDIN_FILENO");
  if(dup2(slaveFd,STDOUT_FILENO)!=STDOUT_FILENO)
    err_exit("ptyFork:dup2-STDOUT_FILENO");
  if(dup2(slaveFd,STDERR_FILENO)!=STDERR_FILENO)
    err_exit("ptyFork:dup2-STDERR_FILENO");

  if(slaveFd>STDERR_FILENO)
    close(slaveFd);

  return 0;
}