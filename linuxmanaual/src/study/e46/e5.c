#include "../../svmsg/svmsg_file.h"

static int clientId;

static void removeQueue(void)
{
  if(msgctl(clientId,IPC_RMID,NULL)==-1)
    errExit("msgctl");
}

static void alarmHandler(int sig)
{
  removeQueue();
  printf("timeout");
  fflush(stdout);
  raise(SIGINT);
}

int main(int argc,char *argv[])
{
  struct requestMsg req;
  struct responseMsg resp;
  int serverId,numMsgs;
  ssize_t msgLen,totBytes;

  struct sigaction sa;

  if(argc!=2||strcmp(argv[1],"--help")==0)
    usageErr("%s pathname\n",argv[0]);

  if(strlen(argv[1])>sizeof(req.pathname)-1)
    cmdLineErr("pathname too long (max:%ld bytes)\n",
	       (long)sizeof(req.pathname)-1);

  sigemptyset(&sa.sa_mask);
  sa.sa_flags=0;
  sa.sa_handler=alarmHandler;;
  if(sigaction(SIGALRM,&sa,NULL)==-1)
    errExit("sigaction");

  alarm(10);

  /* Get server's queue identifier;create queue for response */
  serverId=msgget(SERVER_KEY,S_IWUSR);
  if(serverId==-1)
    errExit("msgget - server message queue");

  clientId=msgget(IPC_PRIVATE,S_IRUSR|S_IWUSR|S_IWGRP);
  if(clientId==-1)
    errExit("msgget - client message queue");

  if(atexit(removeQueue)!=0)
    errExit("atexit");

  /* Send message asking for file named in argv[1] */
  req.mtype=1;			/* Any type will do */
  req.clientId=clientId;
  strncpy(req.pathname,argv[1],sizeof(req.pathname)-1);
  /* Ensure string is terminated */
  req.pathname[sizeof(req.pathname)-1]='\0';
  if(msgsnd(serverId,&req,REQ_MSG_SIZE,0)==-1)
    errExit("msgsnd");

  /* Get first response,which may be failure notification */
  msgLen=msgrcv(clientId,&resp,RESP_MSG_SIZE,0,0);
  if(msgLen==-1)
    errExit("msgrcv");

  if(resp.mtype==RESP_MT_FAILURE){
    printf("%s\n",resp.data);	/* Display msg from server */
    if(msgctl(clientId,IPC_RMID,NULL)==-1)
      errExit("msgctl");
    exit(EXIT_FAILURE);
  }

  /* File was opened successfully by server;process messages
     (including the one already received) containing file data*/
  totBytes=msgLen;		/* Count first message */
  for(numMsgs=1;resp.mtype==RESP_MT_DATA;numMsgs++){
    alarm(10);
    msgLen=msgrcv(clientId,&resp,RESP_MSG_SIZE,0,0);
    alarm(0);   
    if(msgLen==-1)
      errExit("msgrcv");
    totBytes+=msgLen;
  }
  printf("Received %ld bytes (%d messages)\n",(long)totBytes,numMsgs);
  exit(EXIT_SUCCESS);
}
