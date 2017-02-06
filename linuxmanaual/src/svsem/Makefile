#
GPATH=../lib ../time 
VPATH=../lib ../time 
CFLAGS+=-g
OBJECTS=get_num.o error_functions.o 
EXEF:=svsem_demo svsem_mon svsem_setall svsem_create svsem_op svsem_rm
all:$(EXEF)
svsem_rm:svsem_rm.o $(OBJECTS) curr_time.o
svsem_op:svsem_op.o $(OBJECTS) curr_time.o
svsem_create:svsem_create.o $(OBJECTS)
svsem_setall:svsem_setall.o $(OBJECTS)
svsem_demo:svsem_demo.o $(OBJECTS) curr_time.o
svsem_mon:svsem_mon.o $(OBJECTS)
get_num.o:get_num.c tlpi_hdr.h
error_functions.o:error_functions.c error_functions.h ename.c.inc tlpi_hdr.h
curr_time.o:curr_time.c
#print_wait_status.o:print_wait_status.c
#ugid_functions.o:ugid_functions.c
clean:
	$(RM) *.o *.d $(EXEF)