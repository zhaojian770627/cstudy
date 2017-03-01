#
GPATH=../lib ../time
VPATH=../lib ../time
CFLAGS+=-g
OBJECTS=get_num.o error_functions.o
EXEF:=t_flock i_fcntl_locking t_runone
all:$(EXEF)
t_runone:t_runone.o $(OBJECTS) create_pid_file.o region_locking.o
i_fcntl_locking:i_fcntl_locking.o $(OBJECTS) curr_time.o
t_flock:t_flock.o $(OBJECTS) curr_time.o
create_pid_file.o:create_pid_file.c region_locking.h
region_locking.o:region_locking.c
get_num.o:get_num.c tlpi_hdr.h
binary_sems.o:binary_sems.c tlpi_hdr.h
error_functions.o:error_functions.c error_functions.h ename.c.inc tlpi_hdr.h
curr_time.o:curr_time.c
#print_wait_status.o:print_wait_status.c
#ugid_functions.o:ugid_functions.c
clean:
	$(RM) *.o *.d $(EXEF)