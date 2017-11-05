;;; %define _BOOT_DEBUG_
%ifdef _BOOT_DEBUG_
	org	0100h		;调试状态，做成.COM文件，可调试
%else
	org	07c00h		;Boot状态，加载到0:7c00
%endif
;;; ============================================================================
%ifdef	_BOOT_DEBUG_
BaseOfStack		equ	0100h	; 调试状态下堆栈基地址(栈底, 从这个位置向低地址生长)
%else
BaseOfStack		equ	07c00h	; 堆栈基地址(栈底, 从这个位置向低地址生长)
%endif

BaseOfLoader	equ	09000h	;LOADER.BIN　被加载到的位置---段地址
OffsetOfLoader	equ	0100h	;LOADER.BIN　被加载到的位置---偏移地址
RootDirSectors	equ	14	;根目录占用空间
SectorNoOfRootDirectory equ	19 ;Root Directory的第一个扇区
;;; ==================================================================

	jmp	short LABEL_START ;Start to boot.
	nop			  ;这个nop不可少

	;; 下面是FAT12磁盘的头
	BS_OEMName	db 'ZhaoJian' ;OEM String,必须8个字节
	BPB_BytePerSec	dw 512	      ;每扇区字节数
	BPB_SecPerClus	db 1	      ;每族多少扇区
	BPB_RsvdSecCnt	dw 1	      ;Boot记录占用多少扇区
	BPB_NumFATs	db 2	      ;共有多少FAT表
	BPB_RootEntCnt 	dw 224	      ;根目录文件数最大值
	BPB_TotSec16	dw 2880	      ;逻辑扇区总数
	BPB_Media	db 0xf0	      ;媒体描述符
	BPB_FATSz16	dw 9	      ;每FAT扇区数
	BPB_SecPerTrk	dw 18	      ;每磁道扇区数
	BPB_NumHeads	dw 2	      ;刺头数(面数)
	BPB_HiddSec	dd 0	      ;隐藏扇区数
	BPB_TotSec32	dd 0	      ;wTotalSectorCount为0时，这个值记录扇区数
	BS_DrvNum	db 0	      ;中断13的驱动器号
	BS_Reserved1	db 0	      ;未使用
	BS_BootSig	db 29h	      ;扩展移到标记
	BS_VolID	dd 0	      ;卷序列号
	BS_VolLab	db 'ZHAOJIANOS1' ;卷标 11个字符
	BS_FileSysType	db 'FAT12   '	 ;文件系统类型,必须8个字节
LABEL_START:
	mov	ax,cs
	mov	ds,ax
	mov	es,ax
	mov	ss,ax
	mov	sp,BaseOfStack

	;; 软驱复位
	xor	ah,ah
	xor	dl,dl
	int	13h

;;;-----------------------------------------------------------
;;; 下面再Ａ盘的根目录寻找LOADER.bin
	mov	word[wSectorNo],SectorNoOfRootDirectory ;19
LABEL_SEARCH_IN_ROOT_DIR_BEGIN:
	cmp	word[wRootDirSizeForLoop],0 ;判断根目录是否已经读完
	jz	LABEL_NO_LOADERBIN	    ;如果读完表示没有找到LOADER.BIN
	dec	word[wRootDirSizeForLoop]
	mov	ax,BaseOfLoader
	mov	es,ax			; es <- BaseOfStack
	mov	bx,OffsetOfLoader 	; bx <- OffsetOfLoader
	mov	ax,[wSectorNo]		; ax <- Root Directory 中的某扇区号
	mov	cl,1
	call	ReadSector

	mov	si,LoaderFileName 	; ds:si -> "LOADER  BIN"
	mov	di,OffsetOfLoader	; es:di -> BaseOfLoader:0100
	cld
	mov	dx,10h
LABEL_SEARCH_FOR_LOADERBIN:
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
	jmp	LABEL_DIFFERENT	;只要发现不一样的字符就是表示本DirectoryEntry不是我们要找的LOADER.BIN

LABEL_GO_ON:
	inc	di
	jmp	LABEL_CMP_FILENAME ;继续循环

LABEL_DIFFERENT:
	and	di,0ffe0h	;di &=e0 是为了让它指向本条目开头
	add	di,20h		;下一个目录条目
	mov	si,LoaderFileName ;
	jmp	LABEL_SEARCH_FOR_LOADERBIN

LABEL_GOTO_NEXT_SECTOR_IN_ROOT_DIR:
	add	word[wSectorNo],1
	jmp	LABEL_SEARCH_IN_ROOT_DIR_BEGIN

LABEL_NO_LOADERBIN:
	mov	dh,2		;“No LOADER.”
	call	Dispstr

	%ifdef	_BOOT_DEBUG_
	mov	ax, 4c00h		; `.
	int	21h			; /  没有找到 LOADER.BIN, 回到 DOS
%else
	jmp	$			; 没有找到 LOADER.BIN, 死循环在这里
%endif

LABEL_FILENAME_FOUND:			; 找到 LOADER.BIN 后便来到这里继续
	mov	dh,3
	call	Dispstr
	jmp	$			; 代码暂时停在这里
;;;===========================================================
;;; 变量
;Root　Directory占用的扇区数,在循环中会递减至0
wRootDirSizeForLoop	dw	RootDirSectors 
wSectorNo		dw	0 ;要读取的扇区号
bOdd			db	0 ;奇数还是偶数
;;; 字符串
LoaderFileName		db	"LOADER  BIN"
;;; 为简化代码，下面每个字符串的长度均为 MessageLength
; 为简化代码, 下面每个字符串的长度均为 MessageLength
MessageLength		equ	9
BootMessage:		db	"Booting  " ; 9字节, 不够则用空格补齐. 序号 0
Message1		db	"Ready.   " ; 9字节, 不够则用空格补齐. 序号 1
Message2		db	"No LOADER" ; 9字节, 不够则用空格补齐. 序号 2
Message3		db	"FOUND    " ; 9字节, 不够则用空格补齐. 序号 3
;;; ============================================================
Dispstr:
	mov	ax,MessageLength
	mul	dh
	add	ax,BootMessage
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
;;; =====================================================================
	times	510-($-$$)	db 0 ;填充剩下的空间，生成的二进制代码刚好512
	dw	0xaa55		     ;结束标记