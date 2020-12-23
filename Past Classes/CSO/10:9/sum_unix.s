	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14	sdk_version 10, 14
	.globl	_sum_from                    ## -- Begin function foo
	.p2align	4, 0x90

// The hand-written assembly code, below, is the equivalent
// of the following C code for defining a function
// that takes two integer parameters, start and end, and computes
// the sum of the numbers between start and end, inclusive.
//
// int sum_from(int start, int end)
// {
//   int sum = 0;
//   while (start <= end) {
//     sum += start;
//     start++;
//   }
//   return sum;
// }

// The calling convention tells us that start will
// be in the %edi register and end will be in the 
// %esi register.

_sum_from:
	
	push	%rbp
	mov	%rsp,%rbp

	movl	$0,%eax		# sum is in %eax (where the return value goes)

TOP:	# top of loop

	cmp	%esi,%edi	# compare start (%edi) to end (%esi)
	jg	DONE		# if start > end, jump out of loop

	addl	%edi,%eax	# otherwise, add start (%edi) to sum (%eax)
	incl	%edi		# increment start (%esi)

	jmp	TOP		# jump to top of loop
	
DONE:	# out of the loop

	# the sum is already in %eax, so just leave it there as
	# the return value

	pop %rbp
	ret
