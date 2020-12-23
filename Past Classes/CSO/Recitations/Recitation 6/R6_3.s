	.file	"R6_3.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
 	.string "Do something"
main:
 	movl $0, %r8
 	jmp .L2
.L4:
 	cmpl $5, %r8
	jg .L3
	call puts
.L3:
 	addl $1, %r8
.L2:
	cmpl $9, %r8
	jle .L4
	movl $0, %eax # For return statement
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
