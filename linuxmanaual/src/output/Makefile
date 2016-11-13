#
GPATH=../lib ../signals
VPATH=../lib ../signals
OBJECTS=t_sigqueue.o get_num.o error_functions.o 
t_sigqueue:$(OBJECTS)
	cc -o t_sigqueue  $(OBJECTS)
catch_rtsigs:$(OBJECTS)
	cc -o catch_rtsigs $(OBJECTS)
catch_rtsigs.o:catch_rtsigs.c tlpi_hdr.h
t_sigqueue.o:t_sigqueue.c tlpi_hdr.h
get_num.o:get_num.c tlpi_hdr.h
error_functions.o:error_functions.c error_functions.h ename.c.inc tlpi_hdr.h
clean:
	rm  $(OBJECTS)