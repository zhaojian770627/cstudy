#
GPATH=../lib ../time ../users_groups ../procexec
VPATH=../lib ../time ../users_groups ../procexec
CFLAGS+=-g
OBJECTS=get_num.o error_functions.o 
EXEF:=simple_pipe pipe_sync pipe_ls_wc popen_glob fifo_seqnum_server fifo_seqnum_client
all:$(EXEF)
fifo_seqnum_server:fifo_seqnum_server.o $(OBJECTS)
fifo_seqnum_client:fifo_seqnum_client.o $(OBJECTS)
popen_glob:popen_glob.o $(OBJECTS) print_wait_status.o
pipe_ls_wc:pipe_ls_wc.o $(OBJECTS)
pipe_sync:pipe_sync.o $(OBJECTS) curr_time.o
simple_pipe:simple_pipe.o $(OBJECTS)
get_num.o:get_num.c tlpi_hdr.h
error_functions.o:error_functions.c error_functions.h ename.c.inc tlpi_hdr.h
#curr_time.o:curr_time.c
print_wait_status.o:print_wait_status.c
#ugid_functions.o:ugid_functions.c
clean:
	$(RM) *.o *.d $(EXEF)