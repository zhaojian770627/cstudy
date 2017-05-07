#
GPATH=../lib ../tty
VPATH=../lib ../tty
CFLAGS+=-g
OBJECTS=get_num.o error_functions.o 
EXEF:=t_select poll_pipes demo_sigio epoll_input self_pipe
all:$(EXEF)
self_pipe:self_pipe.o $(OBJECTS) 
epoll_input:epoll_input.o $(OBJECTS) 
demo_sigio:demo_sigio.o $(OBJECTS) tty_functions.o
poll_pipes:poll_pipes.o $(OBJECTS)
t_select:t_select.o $(OBJECTS)
get_num.o:get_num.c tlpi_hdr.h
error_functions.o:error_functions.c error_functions.h ename.c.inc tlpi_hdr.h
tty_functions.o:tty_functions.c
clean:
	$(RM) *.o *.d $(EXEF)