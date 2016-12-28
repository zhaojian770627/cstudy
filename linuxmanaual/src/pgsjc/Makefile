#
GPATH=../lib ../time ../users_groups
VPATH=../lib ../time ../users_groups
CFLAGS+=-g
OBJECTS=get_num.o error_functions.o
EXEF:=t_setsid catch_SIGHUP disc_SIGHUP
all:$(EXEF)
disc_SIGHUP:disc_SIGHUP.o $(OBJECTS)
catch_SIGHUP:catch_SIGHUP.o $(OBJECTS)
t_setsid:t_setsid.o $(OBJECTS)
get_num.o:get_num.c tlpi_hdr.h
error_functions.o:error_functions.c error_functions.h ename.c.inc tlpi_hdr.h
#curr_time.o:curr_time.c
#print_wait_status.o:print_wait_status.c
#ugid_functions.o:ugid_functions.c
clean:
	$(RM) *.o *.d $(EXEF)