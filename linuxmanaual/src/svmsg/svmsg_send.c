#include <sys/types.h>
#include <sys/msg.h>
#include "../lib/tlpi_hdr.h"

#define MAX_MTEXT 1024

struct mbuf{
  long mtype;			/* Message bype */
  char mtext[MAX_MTEXT];	/* Message body */
};

/* Print usage info,then exit */
static void usageError(const char *progName,const char *msg)
{
  if(msg!=NULL)
    fprintf(stderr,"%s",msg);
  fprintf(stderr,"Usage:%s [-n] msg-type [msg-text]\n",progName);
  fprintf(stderr,"    -n          Use IPC_NOWAIT flag\n");
  exit(EXIT_FAILURE);
}

int main(int argc,char *argv[])
{
  int msqid,flags,msgLen;
  struct mbuf msg; 		/* Message buffer for msgsnd() */
  int opt;			/* Option character from getopt */

  /* Parse command-line options and arguments */
  flags=0;
  while((opt=getopt(argc,argv,"n"))!=-1){
    if(opt=='n')
      flags|=IPC_NOWAIT;
    else
      usageError(argv[0],NULL);
  }

  msqid=getInt(argv[optind],0,"msqid");
  msg.mtype=getInt(argv[optind+1],0,"msg-type");

  if(argc>optind+2){		/* 'msg-text' was supplied */
    msgLen=strlen(argv[optind+2])+1;
    if(msgLen>MAX_MTEXT)
      cmdLineErr("msg-text too long(max:%d characters)\n",MAX_MTEXT);

    memcpy(msg.mtext,argv[optind+2],msgLen);
  }else{			/* No 'msg-text'==>zero-length msg */
    msgLen=0;
  }

  /* Send message */
  if(msgsnd(msqid,&msg,msgLen,flags)==-1)
    errExit("msgsnd");
  exit(EXIT_SUCCESS);
}
