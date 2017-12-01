/*
 * e1.c
 *
 *  Created on: Sep 21, 2016
 *      Author: root
 */

#include "../lib/tlpi_hdr.h"

void make_image(char *image, char **procv){

}

int main(int argc, char *argv[]) {
  char image[50]="";
  char procv[3][50]={"abc","dddd",0};
  make_image(image,procv);
  exit(EXIT_SUCCESS);
}
