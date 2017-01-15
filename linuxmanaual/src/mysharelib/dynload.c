#include <dlfcn.h>
#include "../lib/tlpi_hdr.h"

int
main(int argc, char *argv[])
{
  void *libHandle;            /* Handle for shared library */
  int (*funcp)(const char*,int,const char*);        /* Pointer to function with no arguments */
  const char *err;

  if (argc != 3 || strcmp(argv[1], "--help") == 0)
    usageErr("%s lib-path func-name\n", argv[0]);

  /* Load the shared library and get a handle for later use */

  libHandle = dlopen(argv[1], RTLD_LAZY);
  if (libHandle == NULL)
    fatal("dlopen: %s", dlerror());

  /* Search library for symbol named in argv[2] */
  (void) dlerror();                           /* Clear dlerror() */
  *(void **) (&funcp) = dlsym(libHandle, argv[2]);
  err = dlerror();
  if (err != NULL)
    fatal("dlsym: %s", err);

  /* Try calling the address returned by dlsym() as a function
     that takes no arguments */

  int i=(*funcp)("1000",GN_GT_0,"libcall");
  printf("%d\n",i);
  dlclose(libHandle);                         /* Close the library */

  exit(EXIT_SUCCESS);
}
