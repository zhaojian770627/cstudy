#
GPATH=../lib ../time ../svsem 
VPATH=../lib ../time ../svsem
CFLAGS+=-g
OBJECTS=get_num.o error_functions.o 
EXEF:=svshm_xfr_writer svshm_xfr_reader svshm_create svshm_attach svshm_rm
all:$(EXEF)
svshm_rm:svshm_rm.o $(OBJECTS) 
svshm_attach:svshm_attach.o $(OBJECTS) 
svshm_create:svshm_create.o $(OBJECTS) 
svshm_xfr_reader:svshm_xfr_reader.o $(OBJECTS) binary_sems.o
svshm_xfr_writer:svshm_xfr_writer.o $(OBJECTS) binary_sems.o
get_num.o:get_num.c tlpi_hdr.h
binary_sems.o:binary_sems.c tlpi_hdr.h
error_functions.o:error_functions.c error_functions.h ename.c.inc tlpi_hdr.h
curr_time.o:curr_time.c
#print_wait_status.o:print_wait_status.c
#ugid_functions.o:ugid_functions.c
clean:
	$(RM) *.o *.d $(EXEF)