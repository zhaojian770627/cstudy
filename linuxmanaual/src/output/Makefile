#
GPATH=../lib ../signals
VPATH=../lib ../signals
OBJECTS= t_sigwaitinfo.o get_num.o error_functions.o signal_functions.o
t_sigwaitinfo: $(OBJECTS)
	cc -o t_sigwaitinfo $(OBJECTS)
t_sigwaitinfo.o:t_sigwaitinfo.c tlpi_hdr.h signal_functions.h
#t_sigqueue:$(OBJECTS)
#	cc -o t_sigqueue  $(OBJECTS)
#catch_rtsigs:$(OBJECTS)
#	cc -o catch_rtsigs $(OBJECTS)
#t_sigsuspend.o:t_sigsuspend.c tlpi_hdr.h signal_functions.h
signal_functions.o:signal_functions.c signal_functions.h tlpi_hdr.h
#catch_rtsigs.o:catch_rtsigs.c tlpi_hdr.h
#t_sigqueue.o:t_sigqueue.c tlpi_hdr.h
get_num.o:get_num.c tlpi_hdr.h
error_functions.o:error_functions.c error_functions.h ename.c.inc tlpi_hdr.h
clean:
	rm  $(OBJECTS)