#
EXEF=hello foobar
#all:$(EXEF)
all:pig.img
pig.img:blank.img boot.bin loader.bin kernel.bin
	cp blank.img pig.img
	dd if=boot.bin of=pig.img  bs=512 count=1 conv=notrunc
	cp pig.img ~/imgs
blank.img:
	dd if=/dev/zero of=blank.img bs=512 count=2880
boot.bin:
	nasm -f bin boot.s -o boot.bin -l boot.lst
loader.bin:
	nasm -f bin loader.s -o loader.bin -l loader.lst
kernel.bin:
	nasm -f elf kernel.s -o kernel.o
	ld -s -m elf_i386 -Ttext 0x30400 -o kernel.bin kernel.o
#hello:
#	nasm -f elf64 hello.s -o hello.o
#	ld -s hello.o -o hello
#foobar:
#	nasm -f elf foo.s -o foo.o
#	gcc -m32 -c -o bar.o bar.c
#	ld -m elf_i386 -s -o foobar foo.o bar.o
clean:
	$(RM) $(EXEF)  *.o *.lst *.bin *.img
