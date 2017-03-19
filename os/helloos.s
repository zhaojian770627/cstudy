	;; hello-os
	;; TAB=4
	org	0x7c00

	jmp	entry
	db	0x90
	db	"HELLOIPL"	;boot sector name 8 byte
	dw	512		;size of per secotr must 512
	db	1		;size of cluster must 1 sector
	dw	1		;Start of FAT (from 1.sector)
	db	2		;2 FAT(must)
	dw	224		;size of root dir,general 224 
	dw	2880		;size of this Disk,2880 sector
	db	0xf0		;disk type,must 0xf0
	dw	9		;length of FAT,9 sector
	dw	18		;per track has 18 sector
	dw	2		;heads 2
	dd	0		;can't partition
	dd	2880		;size of re write disk
	db	0,0,0x29	;fix value
	dd	0xffffffff	;lable num
	db	"HELLO-OS    "	;disk name must 12 byte
	db	"FAT12   "	;disk type name 8 byte
	resb	18		;space 18
entry:
	mov	ax,0
	mov 	ss,ax
	mov	sp,0x7c00
	mov	ds,ax
	mov	es,ax

	mov 	si,msg
putloop:
	mov 	al,[si]
	add	si,1
	cmp	al,0
	je	fin
	mov 	ah,0x0e
	mov	bx,15
	int	0x10
	jmp	putloop
fin:
	hlt
	jmp	fin

msg:
	db	0x0a,0x0a
	db	"hello,zj,I has run"
	db	0x0a
	db	0

	times 	0x1fe-($-$$) db	0
	db	0x55,0xaa