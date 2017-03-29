#
GPATH=../lib ../time ../daemons 
VPATH=../lib ../time ../daemons
CFLAGS+=-g
OBJECTS=get_num.o error_functions.o 
EXEF:=us_xfr_sv us_xfr_cl ud_ucase_sv ud_ucase_cl i6d_ucase_sv i6d_ucase_cl \
is_seqnum_sv is_seqnum_cl id_echo_sv id_echo_cl
all:$(EXEF)
id_echo_sv:id_echo_sv.o $(OBJECTS) inet_sockets.o become_daemon.o
id_echo_cl:id_echo_cl.o $(OBJECTS) inet_sockets.o become_daemon.o
is_seqnum_cl:is_seqnum_cl.o $(OBJECTS) read_line.o
is_seqnum_sv:is_seqnum_sv.o $(OBJECTS) read_line.o
i6d_ucase_cl:i6d_ucase_cl.o $(OBJECTS)
i6d_ucase_sv:i6d_ucase_sv.o $(OBJECTS)
ud_ucase_cl:ud_ucase_cl.o $(OBJECTS) 
ud_ucase_sv:ud_ucase_sv.o $(OBJECTS) 
us_xfr_sv:us_xfr_sv.o $(OBJECTS) 
us_xfr_cl:us_xfr_cl.o $(OBJECTS) 
get_num.o:get_num.c tlpi_hdr.h
become_daemon.o:become_daemon.c tlpi_hdr.h
inet_sockets.o:inet_sockets.c tlpi_hdr.h
error_functions.o:error_functions.c error_functions.h ename.c.inc tlpi_hdr.h
curr_time.o:curr_time.c
#print_wait_status.o:print_wait_status.c
#ugid_functions.o:ugid_functions.c
clean:
	$(RM) *.o *.d $(EXEF)