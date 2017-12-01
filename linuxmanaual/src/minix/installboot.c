/*
 * e1.c
 *
 *  Created on: Sep 21, 2016
 *      Author: root
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>  
#include <errno.h>

#define nil 0
#define IM_NAME_MAX	63

struct	exec {			/* a.out header */
  unsigned char	a_magic[2];	/* magic number */
  unsigned char	a_flags;	/* flags, see below */
  unsigned char	a_cpu;		/* cpu id */
  unsigned char	a_hdrlen;	/* length of header */
  unsigned char	a_unused;	/* reserved for future use */
  unsigned short a_version;	/* version stamp (not used at present) */
  long		a_text;		/* size of text segement in bytes */
  long		a_data;		/* size of data segment in bytes */
  long		a_bss;		/* size of bss segment in bytes */
  long		a_entry;	/* entry point */
  long		a_total;	/* total memory allocated */
  long		a_syms;		/* size of symbol table */

  /* SHORT FORM ENDS HERE */
  long		a_trsize;	/* text relocation size */
  long		a_drsize;	/* data relocation size */
  long		a_tbase;	/* text relocation base */
  long		a_dbase;	/* data relocation base */
};

struct image_header {
	char		name[IM_NAME_MAX + 1];	/* Null terminated. */
	struct exec	process;
};

void report(char *label)
/* installboot: label: No such file or directory */
{
	fprintf(stderr, "installboot: %s: %s\n", label, strerror(errno));
}

void fatal(char *label)
{
	report(label);
	exit(1);
}

void testsize()
{
  printf("unsigned char- %d\n",sizeof(unsigned char));
  printf("unsigned short- %d\n",sizeof(unsigned short));
  printf("long- %d\n",sizeof(long));
}

void make_image(char *image, char **procv){
  char *proc,*file;
  int procn;
  struct image_header ihdr;
  struct stat st;
  FILE *imagef, *procf;

  printf("image:%s\n",image);
  for (procn= 0; (proc= *procv++) != nil; procn++) {
    if ((file= strchr(proc, ':')) != nil) 
      file++; 
    else 
      file= proc;
    printf("procv:%s\n",proc);
    if (stat(file, &st) < 0
	|| (errno= EISDIR, !S_ISREG(st.st_mode))
	|| (procf= fopen(file, "r")) == nil
	)
      fatal(proc) ;


    (void) fclose(procf);
  }
}

int main(int argc, char *argv[]) {
  char image[50]="dddd";
  char *procv[2]={"/home/zj/git/os/minix/zj",0};
  make_image(image,procv);
  exit(EXIT_SUCCESS);
}
