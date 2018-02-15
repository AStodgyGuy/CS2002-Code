	.text
	.file	"sort.c"
	.globl	mergesort
	.p2align	4, 0x90
	.type	mergesort,@function
mergesort:
	.cfi_startproc
	movq	%rcx, %rax
	movq	%rdx, %rcx
	xorl	%edx, %edx
	movq	%rax, %r8
	jmp	sortsub
.Lfunc_end0:
	.size	mergesort, .Lfunc_end0-mergesort
	.cfi_endproc

	.p2align	4, 0x90
	.type	sortsub,@function
sortsub:
	.cfi_startproc
	pushq	%rbp
.Lcfi0:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Lcfi1:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Lcfi2:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Lcfi3:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Lcfi4:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Lcfi5:
	.cfi_def_cfa_offset 56
	subq	$56, %rsp
.Lcfi6:
	.cfi_def_cfa_offset 112
.Lcfi7:
	.cfi_offset %rbx, -56
.Lcfi8:
	.cfi_offset %r12, -48
.Lcfi9:
	.cfi_offset %r13, -40
.Lcfi10:
	.cfi_offset %r14, -32
.Lcfi11:
	.cfi_offset %r15, -24
.Lcfi12:
	.cfi_offset %rbp, -16
	movq	%r8, %r12
	movq	%rcx, %rax
	movq	%rsi, %rbx
	movq	%rdi, %r15
	movq	%rax, %rbp
	subq	%rdx, %rbp
	cmpq	$2, %rbp
	jl	.LBB1_14
	movq	%rbp, %r14
	shrq	%r14
	leaq	(%r14,%rdx), %r13
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movq	%rdx, 32(%rsp)
	movq	%r13, %rcx
	movq	%rax, 16(%rsp)
	movq	%r12, %r8
	callq	sortsub
	movq	%r15, (%rsp)
	movq	%r15, %rdi
	movq	%rbx, %rsi
	movq	%r13, %rdx
	movq	16(%rsp), %rcx
	movq	%r12, 48(%rsp)
	movq	%r12, %r8
	callq	sortsub
	imulq	%rbx, %rbp
	movq	%rbp, 40(%rsp)
	movq	%rbp, %rdi
	callq	malloc
	movq	16(%rsp), %rdx
	movq	%rax, 24(%rsp)
	movq	%r13, 8(%rsp)
	cmpq	%rdx, %r13
	setl	%al
	testq	%r14, %r14
	setne	%cl
	jne	.LBB1_3
	cmpq	%rdx, 8(%rsp)
	jge	.LBB1_13
.LBB1_3:
	movq	24(%rsp), %r14
	movq	8(%rsp), %r13
	movq	32(%rsp), %rbp
	.p2align	4, 0x90
.LBB1_4:
	testb	$1, %al
	je	.LBB1_5
	testb	$1, %cl
	je	.LBB1_7
	movq	%rbp, %r15
	imulq	%rbx, %r15
	movq	(%rsp), %rax
	addq	%rax, %r15
	movq	%r13, %r12
	imulq	%rbx, %r12
	addq	%rax, %r12
	movq	%r15, %rdi
	movq	%r12, %rsi
	callq	*48(%rsp)
	testq	%rax, %rax
	jg	.LBB1_8
	jmp	.LBB1_10
	.p2align	4, 0x90
.LBB1_5:
	movq	%rbp, %r15
	imulq	%rbx, %r15
	addq	(%rsp), %r15
.LBB1_10:
	incq	%rbp
	movq	%r14, %rdi
	movq	%r15, %rsi
	jmp	.LBB1_11
	.p2align	4, 0x90
.LBB1_7:
	movq	%r13, %r12
	imulq	%rbx, %r12
	addq	(%rsp), %r12
.LBB1_8:
	incq	%r13
	movq	%r14, %rdi
	movq	%r12, %rsi
.LBB1_11:
	movq	%rbx, %rdx
	callq	memcpy
	movq	16(%rsp), %rdx
	cmpq	%rdx, %r13
	setl	%al
	addq	%rbx, %r14
	cmpq	8(%rsp), %rbp
	setl	%cl
	jl	.LBB1_4
	cmpq	%rdx, %r13
	jl	.LBB1_4
.LBB1_13:
	movq	32(%rsp), %rax
	imulq	%rbx, %rax
	movq	(%rsp), %rdi
	addq	%rax, %rdi
	movq	24(%rsp), %rbx
	movq	%rbx, %rsi
	movq	40(%rsp), %rdx
	callq	memcpy
	movq	%rbx, %rdi
	addq	$56, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	jmp	free
.LBB1_14:
	addq	$56, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
.Lfunc_end1:
	.size	sortsub, .Lfunc_end1-sortsub
	.cfi_endproc


	.ident	"clang version 5.0.1 (tags/RELEASE_501/final)"
	.section	".note.GNU-stack","",@progbits
