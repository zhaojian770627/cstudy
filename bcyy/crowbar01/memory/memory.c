#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"

static void default_error_handler(MEM_Controller controller,
				  char *filename,int line,char *msg);

static struct MEM_Controller_tag st_default_controller={
  NULL,				/* stderr */
  default_error_handler,
  MEM_FAIL_AND_EXIT
};

/* Point */
MEM_Controller mem_default_controller=&st_default_controller;

typedef union{
  long l_dummy;
  double d_dummy;
  void *p_dummy;
}Align;

#define MARK_SIZE (4)

typedef struct{
  int size;
  char *filename;
  int line;
  Header *prev;
  Header *next;
  unsigned char mark[MARK_SIZE];
}HeaderStruct;

#define ALIGN_SIZE (sizeof(Align))
#define revalue_up_align(val) ((val)?((val)-1)/ALIGN_SIZE+1):0)
#define HEADER_ALIGN_SIZE (revalue_up_align(sizeof(HeaderStruct)))
