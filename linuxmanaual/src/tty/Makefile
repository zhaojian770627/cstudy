#
GPATH=../lib ../time ../svsem 
VPATH=../lib ../time ../svsem
CFLAGS+=-g
OBJECTS=get_num.o error_functions.o 
EXEF:=new_intr no_echo
all:$(EXEF)
no_echo:no_echo.o $(OBJECTS)
new_intr:new_intr.o $(OBJECTS)
error_functions.o:error_functions.c error_functions.h ename.c.inc tlpi_hdr.h
curr_time.o:curr_time.c
#print_wait_status.o:print_wait_status.c
#ugid_functions.o:ugid_functions.c
clean:
	$(RM) *.o *.d $(EXEF)