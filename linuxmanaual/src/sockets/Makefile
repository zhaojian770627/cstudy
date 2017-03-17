#
GPATH=../lib ../time ../svsem 
VPATH=../lib ../time ../svsem
CFLAGS+=-g
OBJECTS=get_num.o error_functions.o 
EXEF:=us_xfr_sv us_xfr_cl ud_ucase_sv ud_ucase_cl i6d_ucase_sv i6d_ucase_cl
all:$(EXEF)
i6d_ucase_cl:i6d_ucase_cl.o $(OBJECTS)
i6d_ucase_sv:i6d_ucase_sv.o $(OBJECTS)
ud_ucase_cl:ud_ucase_cl.o $(OBJECTS) 
ud_ucase_sv:ud_ucase_sv.o $(OBJECTS) 
us_xfr_sv:us_xfr_sv.o $(OBJECTS) 
us_xfr_cl:us_xfr_cl.o $(OBJECTS) 
get_num.o:get_num.c tlpi_hdr.h
binary_sems.o:binary_sems.c tlpi_hdr.h
error_functions.o:error_functions.c error_functions.h ename.c.inc tlpi_hdr.h
curr_time.o:curr_time.c
#print_wait_status.o:print_wait_status.c
#ugid_functions.o:ugid_functions.c
clean:
	$(RM) *.o *.d $(EXEF)