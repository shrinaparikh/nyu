
	// This code, generated by gcc from args.c for UNIX (macOS), shows how
	// the first six parameters are passed in registers and the rest of
	// the parameters (in this case, four more) are pushed onto the stack
	// in reverse order.
	
	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14	sdk_version 10, 14
	.globl	_g                      ## -- Begin function g
	.p2align	4, 0x90
_g:                                     ## @g
## %bb.0:
	pushq	%rbp
	movq	%rsp, %rbp
	movl	$1, %edi
	movl	$2, %esi
	movl	$3, %edx
	movl	$4, %ecx
	movl	$5, %r8d
	movl	$6, %r9d
	pushq	$10
	pushq	$9
	pushq	$8
	pushq	$7
	callq	_foo
	addq	$32, %rsp ///why are you only adding 32 here?

	popq	%rbp
	retq
                                        ## -- End function

.subsections_via_symbols