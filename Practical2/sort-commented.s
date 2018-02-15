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
sortsub:
	.cfi_startproc
	pushq	%rbp
.Lcfi3:
	.cfi_def_cfa_offset 16
.Lcfi4:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Lcfi5:
	.cfi_def_cfa_register %rbp
	subq	$64, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	%rcx, -32(%rbp)
	movq	%r8, -40(%rbp)
	movq	-32(%rbp), %rcx
	subq	-24(%rbp), %rcx
	cmpq	$1, %rcx
	jle	.LBB1_2
	movl	$2, %eax
	movl	%eax, %ecx
	movq	-24(%rbp), %rdx
	movq	-32(%rbp), %rsi
	subq	-24(%rbp), %rsi
	movq	%rsi, %rax
	movq	%rdx, -56(%rbp)
	cqto
	idivq	%rcx
	movq	-56(%rbp), %rcx
	addq	%rax, %rcx
	movq	%rcx, -48(%rbp)
	movq	-8(%rbp), %rdi
	movq	-16(%rbp), %rsi
	movq	-24(%rbp), %rax
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %r8
	movq	%rax, %rdx
	callq	sortsub
	movq	-8(%rbp), %rdi
	movq	-16(%rbp), %rsi
	movq	-48(%rbp), %rdx
	movq	-32(%rbp), %rcx
	movq	-40(%rbp), %r8
	callq	sortsub
	movq	-8(%rbp), %rdi
	movq	-16(%rbp), %rsi
	movq	-24(%rbp), %rdx
	movq	-48(%rbp), %rcx
	movq	-32(%rbp), %r8
	movq	-40(%rbp), %r9
	callq	merge
.LBB1_2:
	addq	$64, %rsp
	popq	%rbp
	retq
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
