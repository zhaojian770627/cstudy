#
all:boot.img
boot.img:blank.img helloos.bin
	cp helloos.bin boot.img
	dd if=blank.img of=boot.img skip=1 seek=1 bs=512 count=2879
	cp boot.img /mnt/share/os/boot.img
blank.img:
	dd if=/dev/zero of=blank.img bs=512 count=2880
helloos.bin:
	nasm -f bin helloos.s -o helloos.bin -l helloos.lst

bootloader.sys:bootpack.bin
	nasm -f bin bootloader.s -o bootloader.bin -l bootloader.lst
	cat bootloader.bin bootpack.bin>bootloader.sys
bootpack.bin:
	gcc -c bootpack.c
	ld bootpack.o -o bootpack.bin -Ttext 0x0 -e HariMain --oformat binary

clean:
	$(RM) *.img *.bin *.sys *.o  *.lst 