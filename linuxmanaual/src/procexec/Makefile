#
GPATH=../lib ../time
VPATH=../lib ../time 
OBJECTS= fork_stdio_buf.o get_num.o error_functions.o curr_time.o
fork_stdio_buf: $(OBJECTS)
	cc -o fork_stdio_buf $(OBJECTS)
fork_stdio_buf.o:fork_stdio_buf.c tlpi_hdr.h 
get_num.o:get_num.c tlpi_hdr.h
error_functions.o:error_functions.c error_functions.h ename.c.inc tlpi_hdr.h
curr_time.o:curr_time.c
clean:
	rm  $(OBJECTS)