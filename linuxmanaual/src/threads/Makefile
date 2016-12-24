#
GPATH=../lib ../time ../users_groups
VPATH=../lib ../time ../users_groups
CFLAGS+=-g
OBJECTS=get_num.o error_functions.o
EXEF:=simple_thread thread_incr thread_incr_mutex thread_multijoin strerror_test
all:$(EXEF)
strerror_test:strerror_test.o $(OBJECTS) -lpthread
thread_multijoin:thread_multijoin.o $(OBJECTS) -lpthread
thread_incr_mutex:thread_incr_mutex.o $(OBJECTS) -lpthread
simple_thread:simple_thread.o $(OBJECTS) -lpthread
thread_incr:thread_incr.o $(OBJECTS) -lpthread
get_num.o:get_num.c tlpi_hdr.h
error_functions.o:error_functions.c error_functions.h ename.c.inc tlpi_hdr.h
curr_time.o:curr_time.c
print_wait_status.o:print_wait_status.c
ugid_functions.o:ugid_functions.c
clean:
	$(RM) *.o *.d $(EXEF)