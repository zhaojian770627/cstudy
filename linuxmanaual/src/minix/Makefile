#
GPATH=../lib 
VPATH=../lib 
CFLAGS+=-g
OBJECTS=get_num.o error_functions.o 
EXEF:=testsize installboot testfs
all:$(EXEF)
testsize:testsize.o
installboot:
	gcc -g -m32 -o installboot installboot.c
testfs:
	gcc -g -m32 -o testfs testfs.c
clean:
	$(RM) *.o *.d $(EXEF)