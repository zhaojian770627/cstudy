#
GPATH=../lib ../time ../users_groups
VPATH=../lib ../time ../users_groups
CFLAGS+=-g
OBJECTS=get_num.o error_functions.o 
EXEF:=dump_utmpx utmpx_login view_lastlog
all:$(EXEF)
view_lastlog:view_lastlog.o $(OBJECTS) ugid_functions.o
utmpx_login:utmpx_login.o $(OBJECTS)
dump_utmpx:dump_utmpx.o $(OBJECTS)
get_num.o:get_num.c tlpi_hdr.h
error_functions.o:error_functions.c error_functions.h ename.c.inc tlpi_hdr.h
#curr_time.o:curr_time.c
#print_wait_status.o:print_wait_status.c
#ugid_functions.o:ugid_functions.c
clean:
	$(RM) *.o *.d $(EXEF)