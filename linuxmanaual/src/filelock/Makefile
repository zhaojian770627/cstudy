#
GPATH=../lib ../time
VPATH=../lib ../time
CFLAGS+=-g
OBJECTS=get_num.o error_functions.o
EXEF:=t_flock i_fcntl_locking
all:$(EXEF)
i_fcntl_locking:i_fcntl_locking.o $(OBJECTS) curr_time.o
t_flock:t_flock.o $(OBJECTS) curr_time.o
get_num.o:get_num.c tlpi_hdr.h
binary_sems.o:binary_sems.c tlpi_hdr.h
error_functions.o:error_functions.c error_functions.h ename.c.inc tlpi_hdr.h
curr_time.o:curr_time.c
#print_wait_status.o:print_wait_status.c
#ugid_functions.o:ugid_functions.c
clean:
	$(RM) *.o *.d $(EXEF)