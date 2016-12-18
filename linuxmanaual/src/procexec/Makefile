#
GPATH=../lib ../time ../users_groups
VPATH=../lib ../time ../users_groups
OBJECTS=get_num.o error_functions.o curr_time.o
all:t_execve envargs t_execlp t_execl closeonexec t_system simple_system system acct_on acct_view t_clone
t_clone:t_clone.c $(OBJECTS)
acct_on:acct_on.c $(OBJECTS)
acct_view:acct_view.o $(OBJECTS) ugid_functions.o
t_system:t_system.o $(OBJECTS) print_wait_status.o 
system:system.o $(OBJECTS)
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
ugid_functions.o:ugid_functions.c
clean:
	rm  $(OBJECTS)