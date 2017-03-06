#include <sys/un.h>
#include <sys/socket.h>
#include <ctype.h>
#include "../lib/tlpi_hdr.h"

#define SV_SOCK_PATH "/tmp/ud_ucase"

/* Maximum size of messages exchanged between client to server */
#define BUF_SIZE 10		
