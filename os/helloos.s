	;; hello-os
	;; TAB=4
CYLS	equ	10
	
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
space:
	resb	18		;space 18
entry:
	mov	ax,0
	mov 	ss,ax
	mov	sp,0x7c00
	mov	ds,ax

	;; read disk
	mov	ax,0x0820
	mov	es,ax
	mov	ch,0		;cylinder 0
	mov	dh,0		;head 0
	mov	cl,2		;sector 2
readloop:	
	mov	si,0		;record failed count
retry:
	mov 	ah,0x02		;ah=0x02:read disk
	mov	al,1		;1 sector
	mov 	bx,0
	mov 	dl,0x00		;A Fd0
	int	0x13		;Call BIOS
	jnc	next		;no error,jmp next
	add	si,1		;error inc si
	cmp	si,5		;cmp si and 5
	jae	error		;when si>=5,jmp error

	mov	ah,0x00
	mov	dl,0x00		;A floppy
	int	0x13		;reset floppy driver
	jmp	retry
next:				;read 18 sector
	mov	ax,es		;add memory address 0x200
	add	ax,0x0020
	mov	es,ax
	add	cl,1
	cmp	cl,18
	jbe	readloop	;if cl<=18 jmp readloop

	mov	cl,1
	add	dh,1
	cmp	dh,2
	jb	readloop
	
	mov	dh,0,
	add	ch,1
	cmp 	ch,CYLS
	jb	readloop	;if ch<CYLS,jmp readloop

	;;jmp haribote.sys 
	jmp	0xc400

error:
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
	db	"load error"
	db	0x0a
	db	0

	times 	0x1fe-($-$$) db	0
	db	0x55,0xaa