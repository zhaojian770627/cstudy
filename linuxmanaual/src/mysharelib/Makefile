#
GPATH=../lib ../time ../users_groups
VPATH=../lib ../time ../users_groups
CFLAGS+=-g -Wall
OBJECTS=get_num.o error_functions.o 
EXEF:=t_calllib
all:$(EXEF)
t_calllib:t_calllib.o libtlpi.so
libtlpi.so:$(OBJECTS)
	gcc -g -shared -Wl,-soname,libltlpi.so -o libtlpi.so $(OBJECTS)
	ln -s libtlpi.so libltlpi.so
get_num.o:get_num.c tlpi_hdr.h
	gcc -g -c -fPIC -Wall ../lib/get_num.c
error_functions.o:error_functions.c error_functions.h ename.c.inc tlpi_hdr.h
	gcc -g -c -fPIC -Wall ../lib/error_functions.c
#curr_time.o:curr_time.c
#print_wait_status.o:print_wait_status.c
#ugid_functions.o:ugid_functions.c
clean:
	$(RM) *.o *.d *.so $(EXEF)