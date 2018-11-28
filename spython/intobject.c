#include "object.h"
#include "intobject.h"


static PyObject* int_add(PyObject* left,PyObject* right);
static void int_print(PyObject* object);
static long int_hash(PyObject* object);

PyTypeObject PyInt_Type={
  PyObject_HEAD_INIT(&PyType_Type),
  "int",
  int_print,
  int_add,
  int_hash
};

PyObject* PyInt_Create(int value)
{
  PyIntObject* object=malloc(sizeof(PyIntObject));
  object->refCount=1;
  object->type=&PyInt_Type;
  object->value=value;
  return (PyObject*)object;
}

static void int_print(PyObject* object)
{
  PyIntObject* intObject=(PyIntObject*)object;
  printf("%d\n",intObject->value);
}

static PyObject* int_add(PyObject* left,PyObject* right)
{
  PyIntObject* leftInt=(PyIntObject*)left;
  PyIntObject* rightInt=(PyIntObject*)right;
  PyIntObject* result=(PyIntObject*)PyInt_Create(0);

  if(result==NULL){
    printf("We have no enouth memory!!");
  }
  else{
    result->value=leftInt->value+rightInt->value;
  }
  return (PyObject*)result;
}

static long int_hash(PyObject* object)
{
  return (long)((PyIntObject*)object)->value;
}
