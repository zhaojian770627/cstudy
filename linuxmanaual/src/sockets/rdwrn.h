#ifndef RDWRN_H
#define RDWRN_H

#include <sys/types.h>

ssize_t readn(int fd,void *buf,size_t len);

ssize_t writen(int fd,const void *buf,size_t len);

#endif
