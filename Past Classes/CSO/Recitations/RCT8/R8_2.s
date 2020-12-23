	.section	__TEXT,__text,regular,pure_instructions
	.globl	_test
	.p2align	4, 0x90

// Use the fibonacci_step function to calculate one step of the fibonacci 
// sequence starting with fibonacci_step(0,1). after calculating each step,
// print out the result and repeat the process to get the first 10 fibonacci 
// numbers: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34

_test:

movq $0,%rdi
call print_int
movq $1,%rdi
call print_int
movq $0, %r4
movq $0, %rsi
movq $1, %rax

L1:
cmpq %7, %r
jg END

L2:
movq %rsi, %rdi //where stopped using % thru rest
movq %rax, %rsi

call fibonacci_step //result with be in %rax

movq %rax, %rdx
call print_int
add $1, %r4
jmp L1

ret
