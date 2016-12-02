#
GPATH=../lib ../time
VPATH=../lib ../time 
OBJECTS= multi_wait.o get_num.o error_functions.o curr_time.o
multi_wait: $(OBJECTS)
	cc -o multi_wait $(OBJECTS)
multi_wait.o:multi_wait.c tlpi_hdr.h 
get_num.o:get_num.c tlpi_hdr.h
error_functions.o:error_functions.c error_functions.h ename.c.inc tlpi_hdr.h
curr_time.o:curr_time.c
clean:
	rm  $(OBJECTS)