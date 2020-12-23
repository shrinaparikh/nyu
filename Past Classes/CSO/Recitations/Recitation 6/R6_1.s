	.file	"R6_1.c"
	.text
	.globl	main
	.type	main, @function
main:
	movl $3, %eax
	movl $4, %ebx
	cmpl %ebx, %eax
	jle .L2 
	addl $1, %eax
	jmp .L3
	.L2:
	addl $1, %ebx
	.L3:
	movl $0, %eax # For return statement
	ret
	
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
