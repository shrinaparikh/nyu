
// This is for UNIX (macOS and Linux)	

	.section	__TEXT,__text,regular,pure_instructions
	.globl	_allocate_cell
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


// ---------------------------------
	
// Given the struct type:
//	
//  typedef struct cell {
//   int val;
//   struct cell *next;
//  } CELL;
//
// the size of CELL is 16 bytes, the offset of val is 0, and the
// offset of next is 8


// This simply calls malloc to allocate one cell and returns the
// address of that cell.

_allocate_cell:
	pushq	%rbp
	movq	%rsp,%rbp

	movq	$16,%rdi	# need to pass 16 to malloc to allocate
	                        # 16 bytes for one cell.
	call	_malloc		# calling malloc

	                        # The address of the cell is already in %rax
				# so just leave it there.
	
	popq	%rbp
	retq



	.globl	_create_list
	.p2align	4, 0x90

//  This function implements the equivalent of
//     CELL *head = NULL;
//     for (int i=10; i > 0; i--) {
//        CELL *p = allocate_cell();
//        p->val = i;
//        p->next = head;
//        head = p;
//     }
//
//  and returns head (i.e. the address of the first
//  cell in the list
//
//  We'll use the following registers to hold the above
//  variables:
//         head in %rax
//         i in %ecx
//         p in %rdx
//  Note that these registers are all caller-saved


_create_list:

	pushq	%rbp
	movq	%rsp,%rbp

	movq	$0,%rax		# head will be in %rax, initialize to NULL (i.e. 0)
	movl	$10,%ecx	# i will be in %ecx, initialize to 10

TOP:	
	cmpl	$0,%ecx		# if i <= 0, jump out of loop
	jle	DONE

				# We're about to call _allocate_cell, above, so need to
				# save any caller-saved registers being used, namely
				# %rax and %rcx. 

	pushq	%rax		# save %rax (containing head) on the stack
	pushq	%rcx		# save %rcx (containing i) on stack

	call	_allocate_cell	# returns the address of the new cell in %rax

	movq	%rax,%rdx	# mov the address into p, in %rdx

                                # After the call, restore the saved caller-saved registers
				# by performing pops in the *reverse* order in which the pushes,
				# above, were performed.
				
	popq	%rcx		# restore i into %ecx
	popq	%rax		# restore head into %rax

	movl	%ecx,0(%rdx)	# move i into p->val (offset of 0 from p)
	movq	%rax,8(%rdx)	# move head into p->next (offset of 8 from p)
	movq	%rdx,%rax	# move p into head

	decl	%ecx		# i--
	
	jmp	TOP

DONE:
	// Out of loop, head is already in %rax
	
	popq	%rbp
	ret




	.globl	_print_list
	.p2align	4, 0x90


// This function takes as a parameter the head
// of a list and performs the following:
//   p = head;
//   while (p != NULL) {
//     printf("%d ", p->val);
//     p = p->next;
//   }
// printf("\n");

//  We'll use the following registers to hold the above
//  variables:
//         head is in %rdi (the first parameter)
//         p in %rbx
//  Note that %rdi is caller-saved and %rbx is callee-saved.


_print_list:

	pushq	%rbp
	movq	%rsp,%rbp

				# Since we will be using a callee-saved register, %rbx,
				# we need to save %rbx before we start using it
				# in this function.
	pushq	%rbx

			        # head is in %rdi, the first parameter register
	mov	%rdi,%rbx	# p is in %rbx, initialized to head

TOP2:	
	cmpq	$0,%rbx		# if p is NULL, jump out of loop
	je	DONE2
				# Calling printf:
				#   We're not using head (%rbi) anymore, so we don't
				#   need to save it before calling printf.
				#   %rbx (containing p) is callee-saved, so we don't
				#   have to save it either.
				
	
	leaq	firstPrintfString(%rip),%rdi	# first parameter to printf
	movq	0(%rbx),%rsi	# p->val is the second parameter to printf

	xorl	%eax,%eax	# printf expects a 0 in %eax, and this is the
				# fastest way of doing that. It's equivalent
				# to saying "movl $0,%eax", but faster.
	
	call	_printf

	movq	8(%rbx),%rbx	# p = p->next  (offset of 8)
	
	jmp	TOP2		# jump to top of loop
	
DONE2:
	# Out of loop, just call printf to print a newline

	# There are no caller-saved registers we need to save
	# before this call to printf.
	
 	leaq	secondPrintfString(%rip),%rdi	# the only parameter to this call
	xorl	%eax,%eax		# remember to zero-out %eax
 	call	_printf

	# Since we saved %rbx (a callee-saved restier) at
	# the beginning of the function, we need to restore
	# it here.

	popq	%rbx
	
	popq	%rbp
	ret
	  
	
// This code defines the two strings literals passed to the two calls to printf(), above.
// Be sure to include the ".section" line below, first.

	.section	__TEXT,__cstring,cstring_literals

// Each string is defined by a label, followed by ".asciz" and the string literal
// in the usual double quotes.

firstPrintfString:                                 
	.asciz	"%d "
secondPrintfString:	
	.asciz	"\n"
	
