;;lib.inc
;;显示AL中的数字
DispAL:
	push	ecx
	push	edx
	push 	edi

	mov	edi,[dwDispPos]

	mov	ah,0fh	;;0000b:黑字 111b:白字
	mov	dl,al
	shr	al,4
	mov	ecx,2
.begin:
	and	al,0111b
	cmp	al,9
	ja	.1
	add	al,'0'
	jmp	.2
.1:	
	sub	al,0ah
	add	al,'A'
.2:
	mov	[gs:edi],ax
	add	edi,2

	mov	al,dl
	loop	.begin
	
	mov	[dwDispPos],edi

	pop	edi
	pop	edx
	pop	ecx

	ret
;;DispAL结束