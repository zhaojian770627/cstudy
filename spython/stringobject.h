#ifndef Py_STRINGOBJECT_H
#define Py_STRINGOBJECT_H
#ifdef __cplusplus
extern "C" {
#endif

  typedef struct tagPyStrObject
  {
    PyObject_HEAD;
    int length;
    long hashValue;
    char value[50];
  }PyStringObject;

  PyObject* PyStr_Create(const char* value);

#ifdef __cplusplus
}
#endif
#endif /* !Py_STRINGOBJECT_H */
