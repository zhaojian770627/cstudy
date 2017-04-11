%include "pm.inc"
	org	07c00h
	jmp	LABEL_BEGIN
	[SECTION .gdt]
	;; GDT
	;; Section			base addr	Limit		Attr
	;; Blank Desc
LABEL_GDT:		Descriptor	0,		0,		0
LABEL_DESC_NORMAL:	Descriptor	0,		0ffffh,		DA_DRW
LABEL_DESC_CODE32:	Descriptor	0,		SegCode32Len-1,	DA_C+DA_32
LABEL_DESC_CODE16:	Descriptor	0,		0ffffh,		DA_C
LABEL_DESC_DATA:	Descriptor	0,		DataLen-1,	DA_DRW
LABEL_DESC_STACK:	Descriptor	0,		TopOfStack,	DA_DRWA+DA_32
LABEL_DESC_TEST:	Descriptor	0500000h,	0ffffh,		DA_DRW
LABEL_DESC_VIDEO:	Descriptor	0B8000h,	0ffffh,		DA_DRW
	;; GDT End

	GdtLen	equ	$-LABEL_GDT ;GDT length
	GdtPtr	dw	GdtLen-1    ;GDT Limit
		dd	0
	;; GDT selector
	SelectorNormal	equ	LABEL_DESC_NORMAL - LABEL_GDT
	SelectorCode32	equ	LABEL_DESC_CODE32 - LABEL_GDT
	SelectorCode16	equ	LABEL_DESC_CODE16 - LABEL_GDT
	SelectorData	equ	LABEL_DESC_DATA	- LABEL_GDT
	SelectorStack	equ	LABEL_DESC_STACK - LABEL_GDT
	SelectorTest 	equ 	LABEL_DESC_TEST - LABEL_GDT
	SelectorVideo	equ	LABEL_DESC_VIDEO - LABEL_GDT
	;; End of [Section .gdt]

	[SECTION .data1]	;data section
	ALIGN 32
	[BITS 32]
LABEL_DATA:
	SPValueInRealMode	dw	0
	;; string
PMMessage:	db	"In Protect Mode now.^-^",0 ;diplay in protected
	OffsetPMMessage	equ	PMMessage - $$
StrTest:	db	"ABCDEFGHIJKLMNOPQRSTUVWXYZ",0
	OffsetStrTest	equ	StrTest - $$
	DataLen	equ	$ - LABEL_DATA
	;; End of [SECTION .data]

	;; global stack sector
	[SECTION .gs]
	ALIGN	32
	[BITS	32]
LABEL_STACK:
	times 	512 db	0

	TopOfStack	equ	$ - LABEL_STACK -1
	;; End of [SECTION .gs]
	
	[SECTION .s16]
	[BITS 16]
LABEL_BEGIN:
	mov 	ax,cs
	mov 	ds,ax
	mov 	es,ax
	mov 	ss,ax
	mov 	sp,0100h

	;; Init 32bit section descriptor
	xor	eax,eax
	mov 	ax,cs
	shl	eax,4
	add	eax,LABEL_SEG_CODE32
	mov	word[LABEL_DESC_CODE32+2],ax
	shr 	eax,16
	mov	byte[LABEL_DESC_CODE32+4],al
	mov	byte[LABEL_DESC_CODE32+7],ah

	;; prepare load GDTR
	xor	eax,eax
	mov	ax,ds
	shl 	eax,4
	add	eax,LABEL_GDT	;eax<-gdt base addr
	mov 	dword[GdtPtr+2],eax ;[GdtPtr+2]<-gdt base addr

	;; Load GDTR
	lgdt	[GdtPtr]

	;; turn off interupt
	cli

	;; open addr bus A20
	in 	al,92h
	or 	al,00000010b
	out	92h,al

	;; prepare switch protect mode
	mov 	eax,cr0
	or	eax,1
	mov	cr0,eax

	;; in protect mode
	jmp	dword SelectorCode32:0
	;; End of [SECTION .s16]

	[SECTION .s32]		;32bit code
	[BITS	32]
LABEL_SEG_CODE32:
	mov	ax,SelectorData
	mov	ds,ax		;Data selector
	mov	ax,SelectorTest
	mov	es,ax
	mov 	ax,SelectorVideo
	mov	gs,ax

	mov	ax,SelectorStack
	mov	ss,ax		 ;Stack section selector

	mov	esp,TopOfStack

	;; Display a string
	
	mov	edi,(80*11+79)*2 ;screen 11 row 79 col

	mov	ah,0ch		 ;red on black
	xor	esi,esi
	xor	edi,edi
	mov	esi,OffsetPMMessage ;source
	mov	edi,(80*10+0)*2	    ;
	cld

.1:
	lodsb
	test	al,al
	jz	.2
	mov	[gs:edi],ax
	add	edi,2
	jmp	.1

.2:	// Here
	
	jmp	$
	SegCode32Len	equ	$-LABEL_SEG_CODE32
	;; END of [SECTION .32