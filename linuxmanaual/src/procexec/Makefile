#
GPATH=../lib ../time
VPATH=../lib ../time 
OBJECTS=get_num.o error_functions.o curr_time.o
all:t_execve envargs t_execlp t_execl closeonexec
closeonexec:closeonexec.o $(OBJECTS)
t_execve:t_execve.o $(OBJECTS)
envargs:envargs.o $(OBJECTS)
t_execlp:t_execlp.o $(OBJECTS)
t_execl:t_execl.o $(OBJECTS)
multi_SIGCHLD.o:multi_SIGCHLD.c tlpi_hdr.h 
get_num.o:get_num.c tlpi_hdr.h
error_functions.o:error_functions.c error_functions.h ename.c.inc tlpi_hdr.h
curr_time.o:curr_time.c
print_wait_status.o:print_wait_status.c
clean:
	rm  $(OBJECTS)