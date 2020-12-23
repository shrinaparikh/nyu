	.section	__TEXT,__text,regular,pure_instructions
	.globl	_element                    ## -- Begin function element
	.p2align	4, 0x90

	// This function takes an array a[] of ints and an int i and
	// simply returns the value of a[i].  The parameters are:
	//    a[] - represented by a 64-bit address in %rdx.
	//    i   - represented by a 32-bit value in %esi.
	
_element:

	push	%rbp
	mov	%rsp,%rbp

	// put a[i] into %eax.  Since the scaled indexing mode (for arrays)
	// of the form (r1,r2,scale) requires that both r1 and r2 be
	// 64-bit registers, we use %rsi for the index, since i (being in %esi) is
	// in the lower half of %rsi.
	
	movl	(%rdi,%rsi,4),%eax  

	// That's it! The result is already in %eax, which is where the return
	// value needs to be.
	
	pop %rbp
	ret
	
