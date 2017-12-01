/*
 * e1.c
 *
 *  Created on: Sep 21, 2016
 *      Author: root
 */

#include "../lib/tlpi_hdr.h"

#define nil 0

void make_image(char *image, char **procv){
  char *proc,*file;
  int procn;

  printf("image:%s\n",image);
  for (procn= 0; (proc= *procv++) != nil; procn++) {
    if ((file= strchr(proc, ':')) != nil) 
      file++; 
    else 
      file= proc;
    printf("procv:%s\n",proc);
  }
}

int main(int argc, char *argv[]) {
  char image[50]="dddd";
  char *procv[3]={"abc","dddd",0};
  make_image(image,procv);
  exit(EXIT_SUCCESS);
}
