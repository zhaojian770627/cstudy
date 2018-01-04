#include <stdio.h>
#include <stdlib.h>

typedef unsigned long  u32_t;	   /* 32 bit type */
typedef struct { u32_t _[2]; } u64_t;

extern u64_t cvul64(long l1,long l2);

int main(int argc, char *argv[]) {
  u64_t u64;
  unsigned long l1=20;
  unsigned long l2=40;
  u64=cvul64(l1,l2);
  printf("_0:%ld\n",u64._[0]);
  printf("_1:%ld\n",u64._[1]);
  return 0;
}
