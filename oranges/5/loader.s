	org	0100h		;调试状态，做成.COM文件，可调试
BaseOfStack		equ	0100h	; 调试状态下堆栈基地址(栈底, 从这个位置向低地址生长)

BaseOfKernelFile	equ	08000h	;KERNEL.BIN　被加载到的位置---段地址
OffsetOfKernelFile	equ	0h	;KERNEL.BIN　被加载到的位置---偏移地址

	jmp	short LABEL_START ;Start to boot.

%include "fat12hdr.inc"

LABEL_START:			;从这里开始
	mov	ax,cs
	mov	ds,ax
	mov	es,ax
	mov	ss,ax
	mov	sp,BaseOfStack

	mov	dh,0		;"Loading "
	call	Dispstr		;显示字符串

	;; 下面在A盘的根目录寻找KERNEL.BIN
	mov	word[wSectorNo],SectorNoOfRootDirectory
		
	;; 软驱复位
	xor	ah,ah
	xor	dl,dl
	int	13h

LABEL_SEARCH_IN_ROOT_DIR_BEGIN:
	cmp	word[wRootDirSizeForLoop],0 ;判断根目录是否已经读完
	jz	LABEL_NO_KERNELBIN	    ;如果读完表示没有找到KERNEL.BIN
	dec	word[wRootDirSizeForLoop]
	mov	ax,BaseOfKernelFile
	mov	es,ax			; es <- BaseOfKernelFile
	mov	bx,OffsetOfKernelFile 	; bx <- OffsetOfKernelFile
	mov	ax,[wSectorNo]		; ax <- Root Directory 中的某扇区号
	mov	cl,1
	call	ReadSector

	mov	si,KernelFileName 	; ds:si -> "KERNEL  BIN"
	mov	di,OffsetOfKernelFile	; es:di -> BaseOfLoader:0100
	cld
	mov	dx,10h
LABEL_SEARCH_FOR_KERNELBIN:
	cmp	dx,0		;循环次数控制
	jz	LABEL_GOTO_NEXT_SECTOR_IN_ROOT_DIR ;如果已经读完了一个Sector
	dec	dx
	mov	cx,11
LABEL_CMP_FILENAME:
	cmp	cx,0
	jz	LABEL_FILENAME_FOUND ;如果比较了11个字符都相等，表示找到
	dec	cx
	lodsb
	cmp	al,byte[es:di]
	jz	LABEL_GO_ON
	jmp	LABEL_DIFFERENT

LABEL_GO_ON:
	inc	di
	jmp	LABEL_CMP_FILENAME ;继续循环

LABEL_DIFFERENT:
	and	di,0ffe0h	;di &=e0 是为了让它指向本条目开头
	add	di,20h		;下一个目录条目
	mov	si,KernelFileName ;
	jmp	LABEL_SEARCH_FOR_KERNELBIN

LABEL_GOTO_NEXT_SECTOR_IN_ROOT_DIR:
	add	word[wSectorNo],1
	jmp	LABEL_SEARCH_IN_ROOT_DIR_BEGIN

LABEL_NO_KERNELBIN:
	mov	dh,2		;“No KERNEL.”
	call	Dispstr		;显示字符串

	%ifdef	_BOOT_DEBUG_
	mov	ax, 4c00h		; `.
	int	21h			; /  没有找到 LOADER.BIN, 回到 DOS
%else
	jmp	$			; 没有找到 LOADER.BIN, 死循环在这里
%endif

LABEL_FILENAME_FOUND:			; 找到 LOADER.BIN 后便来到这里继续
	mov	ax,RootDirSectors
	and	di,0ffe0h	; di -> 当前条目的开始

	push	eax
	mov	eax,[es:di+01ch]
	mov	dword[dwKernelSize],eax ;/ 保存KERNEL.BIN

	add	di,01ah		; di -> 首 Sector
	mov	cx,word[es:di]
	push	cx		;保存此Sector在FAT中的序号
	add	cx,ax
	add	cx,DeltaSectorNo ;cl <- KERNEL.BIN的起始扇区号(0-based)
	mov	ax,BaseOfKernelFile
	mov	es,ax		  ; es <- BaseOfKernelFile
	mov	bx,OffsetOfKernelFile ; bx <- OffsetOfKernelFile
	mov	ax,cx		  ; ax <- Sector 号
LABEL_GOON_LOADING_FILE:
	push	ax
	push	bx
	mov	ah,0eh		; 每读一个扇区就在 "Booting  " 后面打一个点
	mov	al,'.'
	mov	bl,0fh
	int 	10h
	pop	bx
	pop	ax

	mov	cl,1
	call	ReadSector

	pop	ax		;取出此Sector在FAT中的序号
	call	GetFATEntry
	cmp	ax,0fffh
	jz	LABEL_FILE_LOADED
	push	ax		;保存Sector在FAT中的序号
	mov	dx,RootDirSectors
	add	ax,dx
	add	ax,DeltaSectorNo
	add	bx,[BPB_BytsPerSec]
	jmp	LABEL_GOON_LOADING_FILE
LABEL_FILE_LOADED:
	CALL 	KillMotor 	;关闭软驱马达

	mov	dh,1		;"Ready."
	call	Dispstr
;;; **************************************************************
	jmp	$
;;; ***************************************************
	
;;;===========================================================
;;; 变量
;Root　Directory占用的扇区数,在循环中会递减至0
wRootDirSizeForLoop	dw	RootDirSectors 
wSectorNo		dw	0 ;要读取的扇区号
bOdd			db	0 ;奇数还是偶数
dwKernelSize		dd	0 ;KERNEL.BIN文件大小
;;; 字符串
KernelFileName		db	"KERNEL  BIN",0
;;; 为简化代码，下面每个字符串的长度均为 MessageLength
; 为简化代码, 下面每个字符串的长度均为 MessageLength
MessageLength		equ	9
LoadMessage:		db	"Loading  "
Message1		db	"Ready.   " ; 9字节, 不够则用空格补齐. 序号 1
Message2		db	"No KERNEL" ; 9字节, 不够则用空格补齐. 序号 2
Message3		db	"FOUND    " ; 9字节, 不够则用空格补齐. 序号 3
;;; ============================================================
Dispstr:
	mov	ax,MessageLength
	mul	dh
	add	ax,LoadMessage
	mov	bp,ax		;ES:BP=串地址
	mov	ax,ds
	mov	es,ax
	mov	cx,MessageLength
	mov	ax,01301h	;AH=13,AL=01h
	mov	bx,0007h
	mov	dl,0
	int	10h
	ret
	
;;; -----------------------------------------------------------------
;;; 函数名:ReadSector
;;; -------------------------------
;;; 从第ax个Sector开始，将cl个Sector读入es:bx中
ReadSector:
	;; ------------------------------------------------
	;; 由逻辑扇区号求扇区在磁盘中的位置(扇区号->柱面号,起始扇区，磁头号)
	;; 设扇区号为x
	;;			  ┌ 柱面号=y>>1
	;; 	x	   ┌ 商y  ┤
	;; --------------=>┤      └ 磁头号=y&1
	;; 　每磁道扇区数     │
	;;                 └ 余z => 起始扇区号=z+1
	push	bp
	mov	bp,sp
	sub	esp,2		;辟出两个字节的堆栈区域保存要读的扇区数:byte[bp-2]

	mov	byte[bp-2],cl
	push	bx		;保存bx
	mov	bl,[BPB_SecPerTrk] ;bl:除数
	div	bl		   ;y在al中，z在ah中
	inc	ah		   ;z++
	mov	cl,ah		   ;cl<-起始扇区数
	mov	dh,al		   ;dh<-y
	shr	al,1		   ;y>>1(y/BPB_NumHeads
	mov	ch,al		   ;ch<-柱面号
	and	dh,1		   ;dh&1=磁头号
	pop	bx		   ;回复bx
	;; 柱面号，起始扇区，磁头号全部得到
	mov	dl,[BS_DrvNum]	;驱动器号(0 表示Ａ盘)
.GoOnReading:
	mov	ah,2		;读
	mov	al,byte[bp-2]	;读al个扇区
	int	13h
	jc	.GoOnReading	;如果读取错误CF会被置为１，这时就不停地读，直到正确为止

	add	esp,2
	pop	bp

	ret
;;; -----------------------------------------------------------------
;;; 函数名：GetFATEntry
;;; 作用:
;;; 	找到序号为ax的Sector在FAT中的条目，结果放在ax中
;;;  	需要注意的是，中间需要读FAT的扇区到es:bx处，所以函数一开始保存了es和bx
GetFATEntry:
	push	es
	push 	bx
	push	ax
	mov	ax,BaseOfKernelFile
	sub	ax,0100h	;在BaseOfLoader后面留出4K空间用户存放FAT
	mov	es,ax
	pop	ax
	mov	byte[bOdd],0
	mov	bx,3
	mul	bx		;dx:ax=ax*3
	mov	bx,2
	div	bx		;div:ax/2==>ax<-商，dx<-余数
	cmp	dx,0
	jz	LABEL_EVEN
	mov	byte[bOdd],1
LABEL_EVEN:			;偶数
	;; 现在ax中是FATEntry在FAT中的偏移量，下面来计算FATEntry在
	;; 哪个扇区中(FAT占用不止一个扇区)
	xor	dx,dx
	mov	bx,[BPB_BytsPerSec]
	;; dx:ax/BPB/BytePersec
	;; ax<-商(FATEnry所在的扇区相对于FAT的扇区号)
	;; dx<-余数(FATEntry在扇区内的偏移)
	div	bx
	push	dx
	mov	bx,0		;bx<-0 ex:bx=(BaseOfLoader-100):00
	add	ax,SectorNoOfFAT1 ;此句之后的ax就是FATEntry所在的扇区号
	mov	cl,2
	;; 读取FATEntry所在的扇区，一次读两个，避免在边界发生错误
	;; 因为一个FATEntry可能跨越两个扇区
	call	ReadSector
	pop	dx
	add	bx,dx
	mov	ax,[es:bx]
	cmp	byte[bOdd],1
	jnz	LABEL_EVEN_2
	shr	ax,4
LABEL_EVEN_2:
	and 	ax,0fffh
LABEL_GET_FAT_ENTRY_OK:
	pop	bx
	pop	es
	ret
;;; --------------------------------------------------------------------
;;; KillMotor
;;; 	关闭软驱马达		
KillMotor:
	push	dx
	mov	dx,03f2h
	mov	al,0
	out	dx,al
	pop	dx
	ret
