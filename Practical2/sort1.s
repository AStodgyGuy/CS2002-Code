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
	pushq	%rax
.Lcfi6:
	.cfi_def_cfa_offset 64
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
	movq	%r8, %r14
	movq	%rcx, %r15
	movq	%rdx, %r13
	movq	%rsi, %r12
	movq	%rdi, %rbp
	movq	%r15, %rbx
	subq	%r13, %rbx
	cmpq	$2, %rbx
	jl	.LBB1_1
	shrq	%rbx
	addq	%r13, %rbx
	movq	%rbp, %rdi
	movq	%r12, %rsi
	movq	%r13, %rdx
	movq	%rbx, %rcx
	movq	%r14, %r8
	callq	sortsub
	movq	%rbp, %rdi
	movq	%r12, %rsi
	movq	%rbx, %rdx
	movq	%r15, %rcx
	movq	%r14, %r8
	callq	sortsub
	movq	%rbp, %rdi
	movq	%r12, %rsi
	movq	%r13, %rdx
	movq	%rbx, %rcx
	movq	%r15, %r8
	movq	%r14, %r9
	addq	$8, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	jmp	merge
.LBB1_1:
	addq	$8, %rsp
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

	.p2align	4, 0x90
	.type	merge,@function
merge:
	.cfi_startproc
	pushq	%rbp
.Lcfi13:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Lcfi14:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Lcfi15:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Lcfi16:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Lcfi17:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Lcfi18:
	.cfi_def_cfa_offset 56
	subq	$56, %rsp
.Lcfi19:
	.cfi_def_cfa_offset 112
.Lcfi20:
	.cfi_offset %rbx, -56
.Lcfi21:
	.cfi_offset %r12, -48
.Lcfi22:
	.cfi_offset %r13, -40
.Lcfi23:
	.cfi_offset %r14, -32
.Lcfi24:
	.cfi_offset %r15, -24
.Lcfi25:
	.cfi_offset %rbp, -16
	movq	%r9, 48(%rsp)
	movq	%r8, %r14
	movq	%rcx, %r15
	movq	%rdx, %rbx
	movq	%rsi, %rbp
	movq	%rdi, 8(%rsp)
	movq	%r14, %rdi
	subq	%rbx, %rdi
	imulq	%rbp, %rdi
	movq	%rdi, 40(%rsp)
	callq	malloc
	movq	%rax, 24(%rsp)
	cmpq	%r14, %r15
	setl	%al
	movq	%rbx, 32(%rsp)
	movq	%r15, 16(%rsp)
	cmpq	%r15, %rbx
	movq	%r14, %rbx
	setl	%cl
	jl	.LBB2_2
	cmpq	%rbx, 16(%rsp)
	jge	.LBB2_10
.LBB2_2:
	movq	24(%rsp), %r14
	movq	16(%rsp), %r15
	movq	32(%rsp), %r12
	.p2align	4, 0x90
.LBB2_3:
	testb	$1, %al
	je	.LBB2_6
	testb	$1, %cl
	je	.LBB2_7
	movq	%r12, %rdi
	imulq	%rbp, %rdi
	movq	8(%rsp), %rax
	addq	%rax, %rdi
	movq	%r15, %rsi
	imulq	%rbp, %rsi
	addq	%rax, %rsi
	callq	*48(%rsp)
	testq	%rax, %rax
	jle	.LBB2_6
.LBB2_7:
	movq	%rbx, %r13
	leaq	1(%r15), %rbx
	imulq	%rbp, %r15
	addq	8(%rsp), %r15
	movq	%r14, %rdi
	movq	%r15, %rsi
	movq	%rbp, %rdx
	callq	memcpy
	movq	%rbx, %r15
	movq	%r13, %rbx
	jmp	.LBB2_8
	.p2align	4, 0x90
.LBB2_6:
	leaq	1(%r12), %r13
	imulq	%rbp, %r12
	addq	8(%rsp), %r12
	movq	%r14, %rdi
	movq	%r12, %rsi
	movq	%rbp, %rdx
	callq	memcpy
	movq	%r13, %r12
.LBB2_8:
	cmpq	%rbx, %r15
	setl	%al
	addq	%rbp, %r14
	cmpq	16(%rsp), %r12
	setl	%cl
	jl	.LBB2_3
	cmpq	%rbx, %r15
	jl	.LBB2_3
.LBB2_10:
	movq	32(%rsp), %rax
	imulq	%rbp, %rax
	movq	8(%rsp), %rdi
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
.Lfunc_end2:
	.size	merge, .Lfunc_end2-merge
	.cfi_endproc


	.ident	"clang version 5.0.1 (tags/RELEASE_501/final)"
	.section	".note.GNU-stack","",@progbits
