.code32
.section .text
.globl	cvul64
cvul64:
	movl	4(%esp),%eax
	movl	8(%esp),%edx
	movl    12(%esp),%ebx
	movl	%edx,(%eax)
	movl	%ebx,4(%eax)
	ret
	