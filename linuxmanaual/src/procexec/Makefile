#
GPATH=../lib ../time
VPATH=../lib ../time 
OBJECTS= fork_sig_sync.o get_num.o error_functions.o curr_time.o
fork_sig_sync: $(OBJECTS)
	cc -o fork_sig_sync $(OBJECTS)
fork_sig_sync.o:fork_sig_sync.c tlpi_hdr.h 
get_num.o:get_num.c tlpi_hdr.h
error_functions.o:error_functions.c error_functions.h ename.c.inc tlpi_hdr.h
curr_time.o:curr_time.c
clean:
	rm  $(OBJECTS)