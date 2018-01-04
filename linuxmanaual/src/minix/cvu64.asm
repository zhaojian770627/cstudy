[section .text]
global	cvul64
cvul64:
	mov	eax,[esp+4]
	mov	edx,[esp+8]
	mov     ebx,[esp+12]
	mov	[eax],edx
	mov	[eax+4],ebx
	ret
	