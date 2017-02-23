#
GPATH=../lib ../time ../svsem 
VPATH=../lib ../time ../svsem
CFLAGS+=-g
OBJECTS=get_num.o error_functions.o 
EXEF:=psem_unlink psem_create
all:$(EXEF)
psem_unlink:psem_unlink.o $(OBJECTS) -lrt 
psem_create:psem_create.o $(OBJECTS) -lrt 
get_num.o:get_num.c tlpi_hdr.h
binary_sems.o:binary_sems.c tlpi_hdr.h
error_functions.o:error_functions.c error_functions.h ename.c.inc tlpi_hdr.h
curr_time.o:curr_time.c
#print_wait_status.o:print_wait_status.c
#ugid_functions.o:ugid_functions.c
clean:
	$(RM) *.o *.d $(EXEF)