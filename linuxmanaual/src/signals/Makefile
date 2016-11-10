#
GPATH=../lib
VPATH=../lib
OBJECTS=demo_SIGFPE.o get_num.o error_functions.o 
demo_SIGFPE:$(OBJECTS)
	cc -o demo_SIGFPE  $(OBJECTS)
demo_SIGFPE.o:demo_SIGFPE.c tlpi_hdr.h
get_num.o:get_num.c tlpi_hdr.h
error_functions.o:error_functions.c error_functions.h ename.c.inc tlpi_hdr.h
clean:
	rm t_sigaltstack $(OBJECTS)