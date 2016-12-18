#
GPATH=../../lib ../../time
VPATH=../../lib ../../time
OBJECTS=get_num.o error_functions.o curr_time.o
all:e11 e12
e11:e11.c $(OBJECTS)
e12:e12.c $(OBJECTS)

get_num.o:get_num.c tlpi_hdr.h
error_functions.o:error_functions.c error_functions.h ename.c.inc tlpi_hdr.h
curr_time.o:curr_time.c
print_wait_status.o:print_wait_status.c
ugid_functions.o:ugid_functions.c
clean:
	rm  $(OBJECTS)