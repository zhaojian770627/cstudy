#include <sys/types.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <stddef.h>
#include <limits.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include "../lib/tlpi_hdr.h"

#define SERVER_KEY 0x1aaaaaa1	/* Key for server's message queue */

struct requestMsg{		/* Requests (client to server */
  long mtype;			/* Unused */
  int clientId;			/* ID of client's message queue */
  char pathname[PATH_MAX];	/* File to be returned */
};

/* REQ_MSG_SIZE computes size of 'mtext'part of 'requestMsg'
 structure. we use offsetof() to handle the possibility that
there are padding bytes between 'clientId' and 'pathname' fields.*/

#define REQ_MSG_SIZE (offsetof(struct requestMsg,pathname) -\
		      offsetof(struct requestMsg,clientId)+PATH_MAX)

#define RESP_MSG_SIZE 8192

struct responseMsg{		/* Responses (server to client */
  long mtype;			/* One of RESP_MT_* values below */
  char data[RESP_MSG_SIZE];	/* File content/response message */
};

/* Types for response messages sent from server to client */
#define RESP_MT_FAILURE 1	/* File couldn't be opend */
#define RESP_MT_DATA 2		/* Message contains file data */
#define RESP_MT_END 3		/* File data complete */
