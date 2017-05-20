#
GPATH=../lib ../tty 
VPATH=../lib ../tty
CFLAGS+=-g
OBJECTS=get_num.o error_functions.o 
EXEF:=script
all:$(EXEF)
script:script.o $(OBJECTS) tty_functions.o pty_master_open.o pty_fork.o
error_functions.o:error_functions.c error_functions.h ename.c.inc tlpi_hdr.h
tty_functions.o:tty_functions.c
pty_fork.o:pty_fork.c
pty_master_open.o:pty_master_open.c
clean:
	$(RM) *.o *.d $(EXEF)