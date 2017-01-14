#
GPATH=../lib ../time ../users_groups
VPATH=../lib ../time ../users_groups
CFLAGS+=-g -Wall
OBJECTS=get_num.o error_functions.o 
EXEF:=t_calllib
all:$(EXEF)
t_calllib:t_calllib.o libtlpi.so  -ltlpi
#	cc -g -Wall -o t_calllib t_calllib.o -L. -ltlpi
libtlpi.so:$(OBJECTS)
	cc -g -shared -Wl,-soname,libtlpi.so.1 -o libtlpi.so.1.0.1 $(OBJECTS)
	ln -s libtlpi.so.1.0.1 libtlpi.so.1
	ln -s libtlpi.so.1	libtlpi.so
get_num.o:get_num.c tlpi_hdr.h
	cc -g -c -fPIC -Wall ../lib/get_num.c
error_functions.o:error_functions.c error_functions.h ename.c.inc tlpi_hdr.h
	cc -g -c -fPIC -Wall ../lib/error_functions.c
#curr_time.o:curr_time.c
#print_wait_status.o:print_wait_status.c
#ugid_functions.o:ugid_functions.c
clean:
	$(RM) *.o *.d lib* $(EXEF)