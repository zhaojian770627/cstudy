#
GPATH=../../lib ../../time
VPATH=../../lib ../../time 
OBJECTS= e1.o get_num.o error_functions.o curr_time.o
e1: $(OBJECTS)
	cc -o e1 $(OBJECTS)
e1.o:e1.c tlpi_hdr.h 
get_num.o:get_num.c tlpi_hdr.h
error_functions.o:error_functions.c error_functions.h ename.c.inc tlpi_hdr.h
curr_time.o:curr_time.c
clean:
	rm  $(OBJECTS)