	.section	__TEXT,__text,regular,pure_instructions
	.globl	_go
	.p2align	4, 0x90

// These comments below were just pasted from the "Calling Conventions" document
// on the course website.
	
// CALLING CONVENTION
//   Unix (e.g. macOS and Linux)

// Passing Parameters:
// •	First six integer/pointer parameters (in order): %rdi, %rsi, %rdx, %rcx, %r8, %r9
// •	Additional parameters are passed on the stack, pushed in right-to-left (reverse) order.

// Return Value:
// •	%rax (for 64-bit result), %eax (for 32-bit result)

// Caller-Saved Registers (may be overwritten by called function):
// •	%rax , %rcx , %rdx , %rdi , %rsi , %rsp , %r8, %r9, %r10, %r11

// Callee-Saved Registers (must be preserved – or saved and restored – by called function):
// •	%rbx, %rbp, %r12, %r13, %r14, %r15

_go:
	pushq	%rbp
	movq	%rsp,%rbp


// Below is a call to printf, passing just the string "Hello!\n".
// You can see the definition of the label myString at the
// bottom of this file. As seen below, myString  is a label
// corresponding to a memory location in the "text" section,
// where the array of bytes forming the string "Hello!\n" are
// stored.

// Printf is expecting the address of the array of bytes as
// its first parameter. The way that address is specified in
// x86-64 is via in offset from the instruction pointer, %rip,
// indicated by the above label, i.e. via "myString(%rip)".
// The leaq ("load effective address") operation is used to
// compute that address and, in this case, put it in the
// %rdi register as the first parameter to printf.

	leaq	myString(%rip), %rdi	
	call	_printf

// This calls fac(5), by putting 5 in the %edi
// register and calling _fac.
	
	movl	$5,%edi		#32-bit parameter passed in %edi
	call	_fac		# return value will be in %eax

// Since fac returns the result in %eax, to print the
// result we pass the result to print_int() (see called.c)
// by moving the value from %eax into %edi.

	movl	%eax,%edi	# want to print result
	call	_print_int	# don't need return value

// The code below calls silly() (see called.c), with
// the eight parameters being the numbers 1 through 8.
// It illustrates that the first six parameters are
// passed in registers and the other two are pushed
// onto the stack in reverse order, as dictated by
// the calling convention.

	movl    $1,%edi
	movl	$2,%esi
	movl	$3,%edx
	movl	$4,%ecx
	movl	$5,%r8d
	movl	$6,%r9d

// Note that although the last two parameters to silly
// are declared as "int" in called.c, the 64-bit
// push instruction is called to push those parameters
// on the stack.

	pushq	$8
	pushq	$7

// Here's the call to silly().
	call	_silly

// The caller (this code) is responsible for removing any
// data from the stack that it pushed onto the stack. Since
// there were two 8-byte (64-bit) push instructions executed
// above, that data is removed from the stack by adding 16
// (two times 8) to the stack pointer %esp.  Remember that the
// stack grows down, so each of the above 8-byte pushes decreased
// %rsp by 8.

	add	$16,%rsp

// Now calling printf() with the string "Sum is %d\n" and
// the result of calling silly(), by putting the address
// of the string (using leaq as explained above) in %rdi
// and moving the result to be printed from %eax to %esi,
// the register for the second parameter.

	leaq	yourString(%rip),%rdi	  #first param to printf
	movl	%eax,%esi		  #second param to printf
	call	_printf
	
	popq	%rbp
	retq

// This code defines the two strings literals passed to the two calls to printf(), above.
// Be sure to include the ".section" line below, first.

	.section	__TEXT,__cstring,cstring_literals

// Each string is defined by a label, followed by ".asciz" and the string literal
// in the usual double quotes.

myString:                                 
	.asciz	"Hello!\n"
yourString:	
	.asciz	"Sum is %d\n"
	
