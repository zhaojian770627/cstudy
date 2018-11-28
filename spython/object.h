#ifndef Py_OBJECT_H
#define Py_OBJECT_H
#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdlib.h>

#define PyObject_HEAD				\
  int refCount;					\
  struct tagPyTypeObject *type

#define PyObject_HEAD_INIT(typePtr)		\
  0,typePtr

  typedef struct tagPyObject
  {
    PyObject_HEAD;
  }PyObject;

  typedef void (*PrintFun)(PyObject* object);
  typedef PyObject* (*AddFun)(PyObject* left,PyObject* right);
  typedef long (*HashFun)(PyObject* object);

  typedef struct tagPyTypeObject
  {
    PyObject_HEAD;
    char *name;
    PrintFun print;
    AddFun add;
    HashFun hash;
  }PyTypeObject;

PyTypeObject PyType_Type;

#ifdef __cplusplus
}
#endif
#endif /* !Py_OBJECT_H */
