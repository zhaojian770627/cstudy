#
GPATH=../../lib ../../signals
VPATH=../../lib ../../signals
OBJECTS= e1.o get_num.o error_functions.o signal_functions.o
e1: $(OBJECTS)
	cc -o e1 $(OBJECTS)
e1.o:e1.c tlpi_hdr.h signal_functions.h
signal_functions.o:signal_functions.c signal_functions.h tlpi_hdr.h
get_num.o:get_num.c tlpi_hdr.h
error_functions.o:error_functions.c error_functions.h ename.c.inc tlpi_hdr.h
clean:
	rm  $(OBJECTS)