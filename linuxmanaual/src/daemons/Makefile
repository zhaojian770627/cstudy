#
GPATH=../lib ../time ../users_groups
VPATH=../lib ../time ../users_groups
CFLAGS+=-g
OBJECTS=get_num.o error_functions.o 
EXEF:=test_become_daemon daemon_SIGHUP testlog
all:$(EXEF)
testlog:testlog.o $(OBJECTS) become_daemon.o
daemon_SIGHUP:daemon_SIGHUP.o $(OBJECTS) become_daemon.o
test_become_daemon:test_become_daemon.o $(OBJECTS) become_daemon.o
get_num.o:get_num.c tlpi_hdr.h
error_functions.o:error_functions.c error_functions.h ename.c.inc tlpi_hdr.h
#curr_time.o:curr_time.c
#print_wait_status.o:print_wait_status.c
#ugid_functions.o:ugid_functions.c
clean:
	$(RM) *.o *.d $(EXEF)