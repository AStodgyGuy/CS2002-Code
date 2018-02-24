	.text										
	.file	"sort.c"							
	.globl	mergesort							
	.p2align	4, 0x90
	.type	mergesort,@function
mergesort:
	.cfi_startproc
	pushq	%rbp
.Lcfi0:
	.cfi_def_cfa_offset 16
.Lcfi1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Lcfi2:
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	xorl	%eax, %eax
	movl	%eax, %r8d
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	%rcx, -32(%rbp)
	movq	-8(%rbp), %rdi
	movq	-16(%rbp), %rsi
	movq	-24(%rbp), %rcx
	movq	-32(%rbp), %rdx
	movq	%rdx, -40(%rbp)
	movq	%r8, %rdx
	movq	-40(%rbp), %r8
	callq	sortsub
	addq	$48, %rsp
	popq	%rbp
	retq								
.Lfunc_end0:
	.size	mergesort, .Lfunc_end0-mergesort
	.cfi_endproc

	.p2align	4, 0x90
	.type	sortsub,@function
sortsub:								# Name of the function
	.cfi_startproc
	pushq	%rbp						# Setup new stack frame for sortsub function and put it into the rbp register
.Lcfi3:
	.cfi_def_cfa_offset 16
.Lcfi4:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp					# Move the stack pointer to rbp where rbp represents the sortsub function
.Lcfi5:
	.cfi_def_cfa_register %rbp
	subq	$64, %rsp					# Allocate 64 bytes on the stack
	movq	%rdi, -8(%rbp)				# Argument for the sortsub function, varaible stored in rdi has been pushed into the stack and is at position -8 bytes relative to stack pointer, this is variable 'arr'
	movq	%rsi, -16(%rbp)				# Argument for the sortsub function, varaible stored in rsi has been pushed into the stack and is at position -16 bytes relative to stack pointer, this is varaible 'size'
	movq	%rdx, -24(%rbp)				# Argument for the sortsub function, varaible stored in rdx has been pushed into the stack and is at position -24 bytes relative to stack pointer, this is variable 'left'
	movq	%rcx, -32(%rbp)				# Argument for the sortsub function, varaible stored in rcx has been pushed into the stack and is at position -32 bytes relative to stack pointer, this is variable 'right'
	movq	%r8, -40(%rbp)				# Argument for the sortsub function, varaible stored in r8 has been pushed into the stack and is at position -40 bytes relative to stack pointer, this is variable 'comp'
	movq	-32(%rbp), %rcx				# Move the value found at position -32 from the stack pointer to register rcx, in code this is the variable 'right'
	subq	-24(%rbp), %rcx				# Subtract the value at position -24 from the stack pointer from the value in rcx, in code this is the operation 'right - left', store the result in rcx
	cmpq	$1, %rcx					# Compare the constant '1' with the value in rcx, in code this is 'right - left > 1'
	jle	.LBB1_2							# Jump to LBB1_2 if the value held in rcx is less than or equal to 1, in code this is the 'if' statement
	movl	$2, %eax					# Move the constant '2' into register eax
	movl	%eax, %ecx					# Move the value in eax to register ecx, ecx and rcx are the same register
	movq	-24(%rbp), %rdx				# Move the value held in -24 locaions relative to rbp into reigster rdx, this is the variable 'left'
	movq	-32(%rbp), %rsi				# Move the value held in -32 locations relative to rbp into register rsi, this is the variable 'right'
	subq	-24(%rbp), %rsi				# Subtract the value held in -24 locaions relative to rbp from rsi - "right-left"
	movq	%rsi, %rax					# Move the result into the register rax, this will become the quotient of our division further ahead
	movq	%rdx, -56(%rbp)				# Move the variable held in rdx and move it -56 bytes locations relative to rdp, this is done to 'free' up rdx, this moves the variable 'left' to -56 bytes of the stack pointer
	cqto								# cqto is an assembly keyword that converts quadword to octoword preparing the division ((right - left) / 2) incase the division becomes a floating point number
	idivq	%rcx						# idivq divides rax by rcx and stores the remainder in rdx with the result of the division into rax
	movq	-56(%rbp), %rcx				# Move the value held in -56 bytes from the stack pointer to rcx, this holds the variable 'left'
	addq	%rax, %rcx					# Add value held in rcx to the value held in rcx. This is left (rcx) + (right - left) / 2 (rax). Store the result in rcx
	movq	%rcx, -48(%rbp)				# Move the result of that value into a location -48 blocks away from rbp
	movq	-8(%rbp), %rdi				# Move the variable from -8 bytes locations relative to rbp to rdi, this is variable 'arr'
	movq	-16(%rbp), %rsi				# Move the variable from -16 bytes locations relative to rbp to rsi, this is variable 'size'
	movq	-24(%rbp), %rax				# Move the variable from -24 bytes locations relative to rbp to rax, this is variable 'left'
	movq	-48(%rbp), %rcx				# Move the variable from -32 bytes locations relative to rbp to rcx, this is variable 'mid'
	movq	-40(%rbp), %r8				# Move the variable from -40 bytes locations relative to rbp to r8, this is variable 'comp'
	movq	%rax, %rdx					# Unoptimised move statement, rax contains the variable 'left' and it is moved to rdx, this isn't needed
	callq	sortsub						# Call the method sortsub
	movq	-8(%rbp), %rdi				# Move the variable from -8 bytes locations relative to rbp to rdi, this is variable 'arr'
	movq	-16(%rbp), %rsi				# Move the variable from -16 bytes locations relative to rbp to rsi, this is variable 'size'
	movq	-48(%rbp), %rdx				# Move the variable from -48 bytes locations relative to rbp to rax, this is variable 'mid'
	movq	-32(%rbp), %rcx				# Move the variable from -32 bytes locations relative to rbp to rcx, this is variable 'right'
	movq	-40(%rbp), %r8				# Move the variable from -40 bytes locations relative to rbp to r8, this is variable 'comp'
	callq	sortsub						# Call the method sortsub
	movq	-8(%rbp), %rdi				# Move the variable from -8 bytes locations relative to rbp to rdi, this is variable 'arr'
	movq	-16(%rbp), %rsi				# Move the variable from -16 bytes locations relative to rbp to rsi, this is variable 'size'
	movq	-24(%rbp), %rdx				# Move the variable from -24 bytes locations relative to rbp to rdx, this is variable 'left'
	movq	-48(%rbp), %rcx				# Move the variable from -32 bytes locations relative to rbp to rcx, this is variable 'mid'
	movq	-32(%rbp), %r8				# Move the variable from -40 bytes locations relative to rbp to r8, this is variable 'right'
	movq	-40(%rbp), %r9				# Move the variable from -48 bytes locations relative to rbp to r9, this is variable 'comp'
	callq	merge						# Call the method merge
.LBB1_2:								# jle will jump here if 'right - left <= 1'
	addq	$64, %rsp					# Give back 64 bytes of the stack space since there is no condition for else in code
	popq	%rbp						# Pop all the elements in the stack queue
	retq								# Since all elements of the stack have been popped, the stack pointer now points to the top of the stack, retq returns the address of the top of the stack
.Lfunc_end1:
	.size	sortsub, .Lfunc_end1-sortsub
	.cfi_endproc

	.p2align	4, 0x90
	.type	merge,@function
merge:
	.cfi_startproc
	pushq	%rbp
.Lcfi6:
	.cfi_def_cfa_offset 16
.Lcfi7:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Lcfi8:
	.cfi_def_cfa_register %rbp
	subq	$96, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	%rcx, -32(%rbp)
	movq	%r8, -40(%rbp)
	movq	%r9, -48(%rbp)
	movq	-40(%rbp), %rcx
	subq	-24(%rbp), %rcx
	movq	%rcx, -56(%rbp)
	movq	-56(%rbp), %rcx
	imulq	-16(%rbp), %rcx
	movq	%rcx, %rdi
	callq	malloc
	movq	%rax, -64(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -72(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, -80(%rbp)
	movq	$0, -88(%rbp)
.LBB2_1:
	movb	$1, %al
	movq	-72(%rbp), %rcx
	cmpq	-32(%rbp), %rcx
	movb	%al, -89(%rbp)
	jl	.LBB2_3
	movq	-80(%rbp), %rax
	cmpq	-40(%rbp), %rax
	setl	%cl
	movb	%cl, -89(%rbp)
.LBB2_3:
	movb	-89(%rbp), %al
	testb	$1, %al
	jne	.LBB2_4
	jmp	.LBB2_10
.LBB2_4:
	movq	-80(%rbp), %rax
	cmpq	-40(%rbp), %rax
	jge	.LBB2_7
	movq	-72(%rbp), %rax
	cmpq	-32(%rbp), %rax
	jge	.LBB2_8
	movq	-48(%rbp), %rax
	movq	-8(%rbp), %rcx
	movq	-16(%rbp), %rdx
	imulq	-72(%rbp), %rdx
	addq	%rdx, %rcx
	movq	-8(%rbp), %rdx
	movq	-16(%rbp), %rsi
	imulq	-80(%rbp), %rsi
	addq	%rsi, %rdx
	movq	%rcx, %rdi
	movq	%rdx, %rsi
	callq	*%rax
	cmpq	$0, %rax
	jg	.LBB2_8
.LBB2_7:
	movq	-64(%rbp), %rax
	movq	-16(%rbp), %rcx
	movq	-88(%rbp), %rdx
	movq	%rdx, %rsi
	addq	$1, %rsi
	movq	%rsi, -88(%rbp)
	imulq	%rdx, %rcx
	addq	%rcx, %rax
	movq	-8(%rbp), %rcx
	movq	-16(%rbp), %rdx
	movq	-72(%rbp), %rsi
	movq	%rsi, %rdi
	addq	$1, %rdi
	movq	%rdi, -72(%rbp)
	imulq	%rsi, %rdx
	addq	%rdx, %rcx
	movq	-16(%rbp), %rdx
	movq	%rax, %rdi
	movq	%rcx, %rsi
	callq	memcpy
	jmp	.LBB2_9
.LBB2_8:
	movq	-64(%rbp), %rax
	movq	-16(%rbp), %rcx
	movq	-88(%rbp), %rdx
	movq	%rdx, %rsi
	addq	$1, %rsi
	movq	%rsi, -88(%rbp)
	imulq	%rdx, %rcx
	addq	%rcx, %rax
	movq	-8(%rbp), %rcx
	movq	-16(%rbp), %rdx
	movq	-80(%rbp), %rsi
	movq	%rsi, %rdi
	addq	$1, %rdi
	movq	%rdi, -80(%rbp)
	imulq	%rsi, %rdx
	addq	%rdx, %rcx
	movq	-16(%rbp), %rdx
	movq	%rax, %rdi
	movq	%rcx, %rsi
	callq	memcpy
.LBB2_9:
	jmp	.LBB2_1
.LBB2_10:
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rcx
	imulq	-24(%rbp), %rcx
	addq	%rcx, %rax
	movq	-64(%rbp), %rsi
	movq	-56(%rbp), %rcx
	imulq	-16(%rbp), %rcx
	movq	%rax, %rdi
	movq	%rcx, %rdx
	callq	memcpy
	movq	-64(%rbp), %rdi
	callq	free
	addq	$96, %rsp
	popq	%rbp
	retq
.Lfunc_end2:
	.size	merge, .Lfunc_end2-merge
	.cfi_endproc


	.ident	"clang version 5.0.1 (tags/RELEASE_501/final)"
	.section	".note.GNU-stack","",@progbits
