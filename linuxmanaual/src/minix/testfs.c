#include "testfs.h"

void showsize()
{
  printf("unsigned char- %d\n",sizeof(unsigned char));
  printf("unsigned short- %d\n",sizeof(unsigned short));
  printf("long- %d\n",sizeof(long));
  printf("off_t- %d\n",sizeof(off_t));
  printf("inode size -%d\n",sizeof(struct inode));
  printf("super_block size -%d\n",sizeof(struct super_block));
}

void getsuper(char *device){
}

int main(int argc, char *argv[]) {
  char image[50]="zj.img";
  char device[50]="/dev/loop0";
  char *procv[2]={"/home/zj/git/os/minix/zj",0};
  showsize();  
  getsuper(device); 
  exit(EXIT_SUCCESS);
}

