;;; %define _BOOT_DEBUG_
%ifdef _BOOT_DEBUG_
	org	0100h		;调试状态，做成.COM文件，可调试
%else
	org	07c00h		;Boot状态，加载到0:7c00
%endif
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
	BPB_FATSz16	dw 0	      ;每FAT扇区数
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
	call	Dispstr		;调用显示字符串例程
stop:
	halt
	jmp	stop		;无限循环
Dispstr:
	mov	ax,BootMessage
	mov	bp,ax		;ES:BP=串地址
	mov	cx,16		;CX=串长度
	mov	ax,01301h	;AH=13,AL=01h
	mov	bx,000ch	;页号为0(BH=0) 黑底红字(BL=0ch,高亮)
	mov	dl,0
	int	10h
	ret
BootMessage:
	db	"Hello,OS World!"
	times	510-($-$$)	db 0 ;填充剩下的空间，生成的二进制代码刚好512
	dw	0xaa55		     ;结束标记