#include "object.h"
#include "intobject.h"

int
main(int argc,char *argv[])
{
  PyIntObject* o=(PyIntObject*)PyInt_Create(11);
  o->type->print((PyObject*)o); 
  printf("abcd");
}
