#define _BSD_SOURCE

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "inet_sockets.h"
#include "../lib/tlpi_hdr.h"

int
inetConnect(const char *host,const char *service,int type)
{
  struct addrinfo hints;
  struct addrinfo *result,*rp;
  int sfd,s;

  memset(&hints,0,sizeof(struct addrinfo));
  hints.ai_canonname=NULL;
  hints.ai_addr=NULL;
  hints.ai_next=NULL;
  hints.ai_family=AF_UNSPEC;	/* Allows IPv4 or IPv6 */
  hints.ai_socktype=type;

  s=getaddrinfo(host,service,&hints,&result);
  if(s!=0){
    errno=ENOSYS;
    return -1;
  }

  /* Walk */
  for(rp=result;rp!=NULL;rp=rp->ai_next){
    sfd=socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol);
    if(sfd==-1)
      continue;			/* On error,try next address */

    if(connect(sfd,rp->ai_addr,rp->ai_addrlen)!=-1)
      break;			/* Success */

    /* Connect failed:close this socket and try next address */
    close(sfd);
  }

  freeaddrinfo(result);

  return (rp==NULL)?-1:sfd;
}

/* Public interfaces:inetBind() and inetListen() */
static int
inetPassiveSocket(const char *service,int type,socklen_t *addrlen,
		  Boolean doListen,int backlog)
{
  struct addrinfo hints;
  struct addrinfo *result,*rp;
  int sfd,optval,s;

  memset(&hints,0,sizeof(struct addrinfo));
  hints.ai_canonname=NULL;
  hints.ai_addr=NULL;
  hints.ai_next=NULL;
  hints.ai_socktype=type;
  hints.ai_family=AF_UNSPEC;
  hints.ai_flags=AI_PASSIVE;	/* Use wildcard IP address */

  s=getaddrinfo(NULL,service,&hints,&result);
  if(s!=0)
    return -1;

  /* Walk */
  optval=1;

  for(rp=result;rp!=NULL;rp=rp->ai_next){
    sfd=socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol);
    if(sfd==-1)
      continue;

    if(doListen){
      if(setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&optval,
		    sizeof(optval))==-1){
	close(sfd);
	freeaddrinfo(result);
	return -1;
      }
    }

    if(bind(sfd,rp->ai_addr,rp->ai_addrlen)==0)
      break;			/* Success */

    /* bind() failed:close this socket and try next address */
    close(sfd);
  }

  if(rp!=NULL && doListen){
    if(listen(sfd,backlog)==-1){
      freeaddrinfo(result);
      return -1;
    }
  }

  if(rp!=NULL && addrlen!=NULL)
    *addrlen=rp->ai_addrlen;	/* Return address structure size */
  freeaddrinfo(result);

  return (rp==NULL)?-1:sfd;
}

int
inetListen(const char *service,int backlog,socklen_t *addrlen)
{
  return inetPassiveSocket(service,SOCK_STREAM,addrlen,TRUE,backlog);
}

int
inetBind(const char *service,int type,socklen_t *addrlen)
{
  return inetPassiveSocket(service,type,addrlen,FALSE,0);
}

char *
inetAddressStr(const struct sockaddr *addr,socklen_t addrlen,
	       char *addrStr,int addrStrlen)
{
  char host[NI_MAXHOST],service[NI_MAXSERV];

  if(getnameinfo(addr,addrlen,host,NI_MAXHOST,
		 service,NI_MAXSERV,NI_NUMERICSERV)==0)
    snprintf(addrStr,addrStrlen,"(%s,%s)",host,service);
  else
    snprintf(addrStr,addrStrlen,"(?UNKNOWN?)");

  addrStr[addrStrlen-1]='\0';	/* Ensure result is null-terminated */
  return addrStr;
}
