#
GPATH=../lib ../time
VPATH=../lib ../time 
OBJECTS= multi_SIGCHLD.o get_num.o error_functions.o curr_time.o print_wait_status.o
multi_SIGCHLD: $(OBJECTS)
	cc -o multi_SIGCHLD $(OBJECTS)
multi_SIGCHLD.o:multi_SIGCHLD.c tlpi_hdr.h 
get_num.o:get_num.c tlpi_hdr.h
error_functions.o:error_functions.c error_functions.h ename.c.inc tlpi_hdr.h
curr_time.o:curr_time.c
print_wait_status.o:print_wait_status.c
clean:
	rm  $(OBJECTS)