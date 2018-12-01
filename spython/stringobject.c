#include <string.h>
#include "object.h"
#include "stringobject.h"

static void string_print(PyObject* object);
static long string_hash(PyObject* object);
static PyObject* string_add(PyObject* left,PyObject* right);

PyTypeObject PyString_Type={
  PyObject_HEAD_INIT(&PyType_Type),
  "Str",
  string_print,
  string_add,
  string_hash
};

PyObject* PyStr_Create(const char* value)
{
  PyStringObject* object=malloc(sizeof(PyStringObject));
  object->refCount=1;
  object->type=&PyString_Type;
  object->length=(value==NULL)?0:strlen(value);
  object->hashValue=-1;
  memset(object->value,0,50);
  if(value!=NULL){
    strcpy(object->value,value);
  }
  return (PyObject*)object;
}

static void string_print(PyObject* object){
  PyStringObject* strObject=(PyStringObject*)object;
  printf("%s\n",strObject->value);
}

static long string_hash(PyObject* object)
{
  PyStringObject* strObject=(PyStringObject*)object;
  register int len;
  register unsigned char *p;
  register long x;

  if(strObject->hashValue!=-1)
    return strObject->hashValue;
  len=strObject->length;
  p=(unsigned char*)strObject->value;
  x=*p<<7;
  while(--len>=0)
    x=(1000003*x)^*p++;
  x^=strObject->length;
  if(x==-1)
    x=-2;
  strObject->hashValue=x;
  return x;
}

static PyObject* string_add(PyObject* left,PyObject* right)
{
  PyStringObject* leftStr=(PyStringObject*)left;
  PyStringObject* rightStr=(PyStringObject*)right;
  PyStringObject* result=(PyStringObject*)PyStr_Create(NULL);
  if(result==NULL){
    printf("We have no enough memory!!");
    exit(1);
  }else{
    strcpy(result->value,leftStr->value);
    strcat(result->value,rightStr->value);
  }
  return (PyObject*)result;
}
