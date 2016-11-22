#
GPATH=../lib ../time
VPATH=../lib ../time
OBJECTS= ptmr_sigev_thread.o get_num.o error_functions.o itimerspec_from_str.o curr_time.o
ptmr_sigev_thread: $(OBJECTS)
	cc -o ptmr_sigev_thread $(OBJECTS) -lrt
ptmr_sigev_thread.o:ptmr_sigev_thread.c tlpi_hdr.h 
#ptmr_sigev_signal: $(OBJECTS)
#	cc -o ptmr_sigev_signal $(OBJECTS) -lrt
#ptmr_sigev_signal.o:ptmr_sigev_signal.c tlpi_hdr.h 
#t_nanosleep: $(OBJECTS)
#	cc -o t_nanosleep $(OBJECTS)
#t_nanosleep.o:t_nanosleep.c tlpi_hdr.h 
#timed_read: $(OBJECTS)
#	cc -o timed_read $(OBJECTS)
#timed_read.o:timed_read.c tlpi_hdr.h 
#real_timer: $(OBJECTS)
#	cc -o real_timer $(OBJECTS)
#real_timer.o:real_timer.c tlpi_hdr.h 
itimerspec_from_str:itimerspec_from_str.c
curr_time:curr_time.c
get_num.o:get_num.c tlpi_hdr.h
error_functions.o:error_functions.c error_functions.h ename.c.inc tlpi_hdr.h
clean:
	rm  $(OBJECTS)