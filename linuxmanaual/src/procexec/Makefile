#
GPATH=../lib 
VPATH=../lib 
OBJECTS= t_vfork.o get_num.o error_functions.o 
t_vfork: $(OBJECTS)
	cc -o t_vfork $(OBJECTS)
t_vfork.o:t_vfork.c tlpi_hdr.h 
get_num.o:get_num.c tlpi_hdr.h
error_functions.o:error_functions.c error_functions.h ename.c.inc tlpi_hdr.h
clean:
	rm  $(OBJECTS)