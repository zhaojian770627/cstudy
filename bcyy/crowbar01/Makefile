TARGET=crowbar
CC=gcc
OBJS=\
lex.yy.o \
y.tab.o \
eval.o \
string.o \
string_pool.o \
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
	$(CC) $(OBJS) -o $@ -lm
clean:
	rm -f *.o lex.yy.c y.tab.c y.tab.h *~ ./debug/*.o ./memory/*.o *.output
./memory/mem.o:
	cd ./memory;$(MAKE);
./debug/dbg.o:
	cd ./debug;$(MAKE);
y.tab.h:crowbar.y
	yacc -dv crowbar.y
y.tab.o:y.tab.c crowbar.h MEM.h
	$(CC) -c -g $*.c $(INCLUDES)
lex.yy.o:lex.yy.c crowbar.h MEM.h
	$(CC) -c -g $*.c $(INCLUDES)
y.tab.c:
	yacc -dv crowbar.y
lex.yy.c:crowbar.lex crowbar.y y.tab.h
	lex crowbar.lex

string.o:crowbar.h
string_pool.o:crowbar.h
util.o:crowbar.h
native.o:crowbar.h
error.o:crowbar.h
error_message.o:error_message.c crowbar.h