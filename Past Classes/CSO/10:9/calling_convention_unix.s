	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14	sdk_version 10, 14
	.globl	_foo                    ## -- Begin function foo
	.p2align	4, 0x90
_foo:                                   ## @foo

// Take a look at calling_convention_unix.c, which this code
// was generated from by calling gcc as follows:
//
// gcc -Og -S -fno-asynchronous-unwind-tables calling_convention_unix.s
//
// This code shows that the Unix (e.g. macOS and linux) calling
// convention says that the first five parameters in a function
// call (in this case 32-bit ints) are placed in the %edi,
// %esi, %edx, %ecx, and %r8d 32-bit registers, respectively.
// It also shows that a 32-bit return value is placed in
// the %eax register.
//
// Note: If the five parameters were 64-bit values, they would be
// placed in the %rdi, %rsi, %rdx, %rcx, and %r8 registers,
// respectively. A 64-bit return value would be place in %rax.	
	
	pushq	%rbp
	movq	%rsp, %rbp
	movl	$1, %edi	# first parameter in %edi
	movl	$2, %esi	# second parameter in %esi
	movl	$3, %edx	# third parameter in %edx
	movl	$4, %ecx	# fourth parameter in %ecx
	movl	$5, %r8d	# fifth parameter in %rd8

	callq	_f		# call to f(), return
				# value will be in %eax

	incl	%eax		# incrementing the value
 	                        # returned by f, result
	                        # is left in %eax as the
	                        # return value of foo
	
	popq	%rbp
	retq
                                        ## -- End function

.subsections_via_symbols
