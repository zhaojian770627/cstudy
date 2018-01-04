#
GPATH=../lib 
VPATH=../lib 
CFLAGS+=-g
OBJECTS=get_num.o error_functions.o 
EXEF:=testsize cvul64m  #installboot testfs
all:$(EXEF)
cvul64m:
	gcc -g -m32 -o cvul64m.o -c cvul64m.c
	#as --32 -g cvu64.s -o cvu64.o
	nasm -f elf32 cvu64.asm -g -F dwarf -o cvu64.o
	gcc -g -m32 cvu64.o cvul64m.o -o cvul64m
	#ld -m elf_i386 -s -o cvul64test cvul64test.o cvu64.o
testsize:
	gcc -g -m32 -o testsize testsize.c
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