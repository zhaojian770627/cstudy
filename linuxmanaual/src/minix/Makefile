#
GPATH=../lib 
VPATH=../lib 
CFLAGS+=-g
OBJECTS=get_num.o error_functions.o 
EXEF:=testsize installboot
all:$(EXEF)
testsize:testsize.o
installboot:
	gcc -m32 -o installboot installboot.c
clean:
	$(RM) *.o *.d $(EXEF)