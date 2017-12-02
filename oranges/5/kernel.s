; 编译链接方法
; $ nasm -f elf kernel.asm -o kernel.o
; $ ld -s kernel.o -o kernel.bin    #‘-s’选项意为“strip all”

	SELECTOR_KERNEL_CS	equ	8

	;; 导入函数
	extern gdt_ptr

	[SECTION .bss]
	StackSpace	resp	2*1024
StackTop:			;栈顶
	[section .text]	; 代码在此

global _start	; 导出 _start

_start:
	;; 把esp从LOADER挪到KERNEL
	mov	esp,StackTop	;堆栈在bss段中

	sdgt	[gdt_ptr]	;cstart()中将会用到gdt_ptr
	call	cstart		;此函数中改变了gdt_ptr,让它指向新的gdt
	ldgt	[gdt_ptr]	;使用新的GDT
	;; ldgt	[idt_ptr]
	jmp	SECTOR_KERNEL_CS:csinit
csinit:
	push	0
	popfd			;Pop top of stack into EFALGS
	hlt