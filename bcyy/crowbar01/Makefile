TARGET=crowbar
CC=gcc
OBJS=\
util.o \
native.o \
error.o \
error_message.o \
./memory/mem.o \
./debug/dbg.o

CFLAGS=-c -g -Wall -Wswitch-enum -ansi -pedantic -DDEBUG
INCLUDES=\

$(TARGET):$(OBJS)
#	cd ./memory;$(MAKE);
#	cd ./debug;$(MAKE);
#	$(CC) $(OBJS) -o $@ -lm
clean:
	rm -f *.o lex.yy.c y.tab.c y.tab.h *~
./memory/mem.o:
	cd ./memory;$(MAKE);
./debug/dbg.o:
	cd ./debug;$(MAKE);

util.o:crowbar.h
native.o:crowbar.h
error.o:crowbar.h
error_message.o:error_message.c crowbar.h