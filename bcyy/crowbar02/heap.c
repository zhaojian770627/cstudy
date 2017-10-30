#include <stdio.h>
#include <string.h>
#include "MEM.h"
#include "DBG.h"
#include "crowbar.h"

static void
check_gc(CRB_Interpreter *inter)
{
#if 0
  crb_grabage_collect(inter);
#endif
  if(inter->heap.current_heap_size>inter->heap.current_threshold){
    /* fprintf(stderr,"garbage collecting..."); */
    crb_garbate_collect(inter);
    /* fprintf(stderr,"done.\n"); */
    inter->heap.current_threshold
      =inter->heap.current_heap_size+HEAP_THRESHOLD_SIZE;
  }
}

static CRB_Object *
alloc_object(CRB_Interpreter *inter,ObjectType type)
{
  CRB_Object *ret;

  check_gc(inter);
  ret=MEM_Malloc(sizeof(CRB_Object));
  inter->heap.current_heap_size+=sizeof(CRB_Object);
  ret->type=type;
  ret->marked=CRB_FALSE;
  ret->prev=NULL;
  ret->next=inter->heap.header;
  if(ret->next){
    ret->next->prev=ret;
  }
  return ret;
}
