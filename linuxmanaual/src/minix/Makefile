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
testfs:lib.o testfs.o
	gcc -m32 -o testfs testfs.o lib.o
testfs.o:
	gcc -g -m32 -o testfs.o -c testfs.c
lib.o:
	gcc -g -m32 -o lib.o -c lib.c
clean:
	$(RM) *.o *.d $(EXEF)