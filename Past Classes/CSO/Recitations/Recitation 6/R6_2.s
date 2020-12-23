	.file	"R6_2.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
 	.string "%d\n"
main:
	movl $3, %ebx
	jmp .L2
.L3:
	call printf # uses .LC0
	subl $1, %ebx
.L2:
	cmpl $0, %ebx
	jns .L3
	movl $0, %eax # For return statement
 ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
