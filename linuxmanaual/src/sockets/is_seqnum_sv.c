#define _BSD_SOURCE		/* To get definitions of NI_MAXHOST and
				 NI_MAXSERV from <netdb.h> */
#include <netdb.h>
#include "is_seqnum.h"

#define BACKLOG 50

int 
main(int argc,char *argv[])
{
  uint32_t seqNum;
  char reqLenStr[INT_LEN];	/* Length of requested sequence */
  char seqNumStr[INT_LEN];	/* Start of granted sequence */
  struct sockaddr_storage claddr;
  int lfd,cfd,optval,reqLen;
  socklen_t addrlen;
  struct addrinfo hints;
  struct addrinfo *result,*rp;
#define ADDRSTRLEN (NI_MAXHOST+NI_MAXSERV+10)
  char addrStr[ADDRSTRLEN];
  char host[NI_MAXHOST];
  char service[NI_MAXSERV];

  if(argc>1 && strcmp(argv[1],"--help")==0)
    usageErr("%s [init-seq-num]\n",argv[0]);

  seqNum=(argc>1)?getInt(argv[1],0,"init-seq-num"):0;

  if(signal(SIGPIPE,SIG_IGN)==SIG_ERR)
    errExit("signal");

  /* Call getaddrinfo() to obtain a list of addresses that
   we can try binding to */

  memset(&hints,0,sizeof(struct addrinfo));
  hints.ai_canonname=NULL;
  hints.ai_addr=NULL;
  hints.ai_next=NULL;
  hints.ai_socktype=SOCK_STREAM;
  hints.ai_family=AF_UNSPEC;	/* Allows IPv4 or IPv6 */
  /* Wildcar IP address;service name is numeric */
  hints.ai_flags=AI_PASSIVE|AI_NUMERICSERV;

  if(getaddrinfo(NULL,PORT_NUM,&hints,&result)!=0)
    errExit("getaddrinfo");



  freeaddrinfo(result);
}
