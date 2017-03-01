#include <sys/stat.h>
#include <fcntl.h>
#include "region_locking.h"
#include "create_pid_file.h"
#include "../lib/tlpi_hdr.h"

/* Large enough to hold maximum PID as string*/
#define BUF_SIZE 100

/* Open/create the file named in 'pidFile',lock it,optionally set the
 close-on-exec flag for the file descriptor,write out PID into the file,
and (in case the caller is interested) return the file descriptor 
referring to the locked file.The caller is responsible for deleting
 pidFile' file (just) before process termination.'progname' should be 
the name of the calling program (i.e.,argv[0] or similar),and is used only 
for diagnostic messages.if we can't open 'pidFile',or we encounter some 
other error,then we print an appropriate diagnostic and terminate*/
int createPidFile(const char *progName,const char *pidFile,int flags)
{
  int fd;
  char buf[BUF_SIZE];

  fd=open(pidFile,O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
  if(fd==-1)
    errExit("Could not open PID file %s",pidFile);

  if(flags & CPF_CLOEXEC){
    /* Set the close-on-exec file descriptor flag */
    flags=fcntl(fd,F_GETFD);	/* Fetch flags */

    if(flags==-1)
      errExit("Could not get flags for PID file %s",pidFile);

    flags|=FD_CLOEXEC;		/* Update flags */

    if(fcntl(fd,F_SETFD,flags)==-1) /* Update flags */
      errExit("Could not set flags for PID file %s",pidFile);
  }

  if(lockRegion(fd,F_WRLCK,SEEK_SET,0,0)==-1){
    if(errno==EAGAIN||errno==EACCES)
      fatal("PID file '%s' is locked;probably "
	    "'%s' is already running",pidFile,progName);
    else
      errExit("Unable to lock PID file '%s'",pidFile);
  }

  if(ftruncate(fd,0)==-1)
    errExit("Could not truncate PID file '%s'",pidFile);

  snprintf(buf,BUF_SIZE,"%ld\n",(long)getpid());
  if(write(fd,buf,strlen(buf))!=strlen(buf))
    fatal("Writing to PID file '%s'",pidFile);

  return fd;
}
