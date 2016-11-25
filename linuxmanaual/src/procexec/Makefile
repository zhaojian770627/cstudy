#
GPATH=../lib 
VPATH=../lib 
OBJECTS= fork_file_sharing.o get_num.o error_functions.o 
fork_file_sharing: $(OBJECTS)
	cc -o fork_file_sharing $(OBJECTS)
fork_file_sharing.o:fork_file_sharing.c tlpi_hdr.h 
get_num.o:get_num.c tlpi_hdr.h
error_functions.o:error_functions.c error_functions.h ename.c.inc tlpi_hdr.h
clean:
	rm  $(OBJECTS)