#ifndef Py_INTOBJECT_H
#define Py_INTOBJECT_H
#ifdef __cplusplus
extern "C" {
#endif
  typedef struct tagPyIntObject
  {
    PyObject_HEAD;
    int value;
  }PyIntObject;

  PyObject* PyInt_Create(int value);

#ifdef __cplusplus
}
#endif
#endif /* !Py_INTOBJECT_H */
