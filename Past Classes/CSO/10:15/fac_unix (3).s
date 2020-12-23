	.section	__TEXT,__text,regular,pure_instructions
	.globl	_fac                    ## -- Begin function fac
	.p2align	4, 0x90


	// This function computes fac(x), given a 32-bit parameter x,
	// returning a 32-bit result. As specified by the calling
	// convention, the parameter x will be in %edi and the 32-bit
	// result must be put in %eax.
_fac:

	push	%rbp
	mov	%rsp,%rbp

	// We choose to put prod (the running product) in
	// %eax, since the result must be placed in %eax
	// anyway.
	
	movl	$1,%eax		// prod = 1
	movl	$1,%ecx		// i = 1

TOP:
	cmpl	%edi,%ecx	// compare i to x (read the comparison from right to left)
	jg	DONE		// if i is greater than x, jump out of loop.
	imull	%ecx,%eax	// prod = prod * i
	incl	%ecx		// i++
	jmp	TOP	 	// jump back to top of loop

DONE:	
	
	pop %rbp
	ret
	
