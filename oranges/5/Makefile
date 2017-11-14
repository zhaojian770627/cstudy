#
EXEF=hello
all:$(EXEF)
hello:
	nasm -f elf64 hello.s -o hello.o
	ld -s hello.o -o hello
clean:
	$(RM) $(EXEF)  *.o *.lst *.bin
