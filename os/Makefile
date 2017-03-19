#
all:boot.img
boot.img:blank.img helloos.bin
	cp helloos.bin boot.img
	dd if=blank.img of=boot.img skip=1 seek=1 bs=512 count=2879
blank.img:
	dd if=/dev/zero of=blank.img bs=1k count=1024
helloos.bin:
	nasm -f bin helloos.s -o helloos.bin
clean:
	$(RM) boot.img blank.img helloos.img helloos.bin 