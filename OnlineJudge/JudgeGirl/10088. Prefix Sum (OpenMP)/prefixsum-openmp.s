	.file	"prefixsum-openmp.c"
	.text
	.p2align 4,,15
	.type	main._omp_fn.1, @function
main._omp_fn.1:
.LFB31:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movq	%rdi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movl	8(%rdi), %ebx
	call	omp_get_num_threads
	movl	%eax, %ebp
	call	omp_get_thread_num
	movl	%eax, %esi
	leal	-1(%rbx), %eax
	cltd
	idivl	%ebp
	cmpl	%edx, %esi
	jge	.L8
	addl	$1, %eax
	xorl	%edx, %edx
.L8:
	imull	%eax, %esi
	addl	%esi, %edx
	leal	(%rdx,%rax), %ecx
	cmpl	%ecx, %edx
	jge	.L1
	movq	(%r12), %r11
	leal	1(%rdx), %r8d
	leal	1(%rcx), %r10d
	.p2align 4,,10
	.p2align 3
.L5:
	movl	(%r11), %edi
	movl	%r8d, %esi
	leal	1(%r8), %r9d
	movslq	%r8d, %r8
	imull	%edi, %esi
	movl	%esi, %eax
	cltd
	idivl	%ebx
	leal	1(%rax), %ecx
	leal	(%rsi,%rdi), %eax
	cltd
	idivl	%ebx
	movl	block(,%r8,4), %edx
	cmpl	%eax, %ecx
	jg	.L6
	leal	1(%rax), %esi
	.p2align 4,,10
	.p2align 3
.L7:
	movslq	%ecx, %rax
	addl	$1, %ecx
	addl	%edx, prefix_sum(,%rax,4)
	cmpl	%esi, %ecx
	jne	.L7
.L6:
	cmpl	%r10d, %r9d
	je	.L1
	movl	%r9d, %r8d
	jmp	.L5
.L1:
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	.p2align 4,,1
	ret
	.cfi_endproc
.LFE31:
	.size	main._omp_fn.1, .-main._omp_fn.1
	.p2align 4,,15
	.type	main._omp_fn.0, @function
main._omp_fn.0:
.LFB30:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movq	%rdi, %r13
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	movl	16(%rdi), %ebx
	call	omp_get_num_threads
	movl	%eax, %ebp
	call	omp_get_thread_num
	movl	%eax, %ecx
	movl	%ebx, %eax
	cltd
	idivl	%ebp
	cmpl	%edx, %ecx
	jge	.L18
	addl	$1, %eax
	xorl	%edx, %edx
.L18:
	imull	%eax, %ecx
	leal	(%rcx,%rdx), %r10d
	leal	(%r10,%rax), %r11d
	cmpl	%r11d, %r10d
	jge	.L11
	movq	0(%r13), %rbp
	.p2align 4,,10
	.p2align 3
.L15:
	movl	0(%rbp), %r8d
	movl	%r10d, %ecx
	addl	$1, %r10d
	imull	%r8d, %ecx
	movl	%ecx, %eax
	cltd
	idivl	%ebx
	leal	1(%rax), %esi
	leal	(%rcx,%r8), %eax
	cltd
	idivl	%ebx
	cmpl	%eax, %esi
	jg	.L20
	movq	8(%r13), %r12
	leal	1(%rax), %r9d
	xorl	%r8d, %r8d
	.p2align 4,,10
	.p2align 3
.L17:
	movl	(%r12), %ecx
	movl	%esi, %edx
	roll	%cl, %edx
	addl	%ecx, %edx
	xorl	%ecx, %edx
	addl	%edx, %r8d
	movslq	%esi, %rdx
	addl	$1, %esi
	cmpl	%r9d, %esi
	movl	%r8d, prefix_sum(,%rdx,4)
	jne	.L17
	movslq	%r10d, %rax
	cmpl	%r11d, %r10d
	movl	%r8d, block(,%rax,4)
	jne	.L15
.L11:
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
.L20:
	.cfi_restore_state
	xorl	%r8d, %r8d
	movslq	%r10d, %rax
	cmpl	%r11d, %r10d
	movl	%r8d, block(,%rax,4)
	jne	.L15
	jmp	.L11
	.cfi_endproc
.LFE30:
	.size	main._omp_fn.0, .-main._omp_fn.0
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d %u"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB29:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movl	$4, %edi
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$72, %rsp
	.cfi_def_cfa_offset 96
	leaq	8(%rsp), %rbx
	leaq	12(%rsp), %rbp
	call	omp_set_num_threads
	.p2align 4,,10
	.p2align 3
.L22:
	xorl	%eax, %eax
	movq	%rbp, %rdx
	movq	%rbx, %rsi
	movl	$.LC0, %edi
	call	__isoc99_scanf
	cmpl	$2, %eax
	jne	.L29
	leaq	32(%rsp), %rsi
	xorl	%edx, %edx
	movl	$main._omp_fn.0, %edi
	movq	%rbx, 32(%rsp)
	movq	%rbp, 40(%rsp)
	movl	$4, 48(%rsp)
	call	GOMP_parallel_start
	leaq	32(%rsp), %rdi
	call	main._omp_fn.0
	call	GOMP_parallel_end
	movl	48(%rsp), %r8d
	cmpl	$1, %r8d
	jle	.L24
	leal	-2(%r8), %edx
	movl	$block+4, %eax
	leaq	block+8(,%rdx,4), %rdi
	.p2align 4,,10
	.p2align 3
.L26:
	movl	-4(%rax), %ecx
	addl	%ecx, (%rax)
	addq	$4, %rax
	cmpq	%rdi, %rax
	jne	.L26
.L24:
	leaq	16(%rsp), %rsi
	xorl	%edx, %edx
	movl	$main._omp_fn.1, %edi
	movl	%r8d, 24(%rsp)
	movq	%rbx, 16(%rsp)
	call	GOMP_parallel_start
	leaq	16(%rsp), %rdi
	call	main._omp_fn.1
	call	GOMP_parallel_end
	movl	8(%rsp), %esi
	movl	$prefix_sum, %edi
	call	output
	jmp	.L22
.L29:
	addq	$72, %rsp
	.cfi_def_cfa_offset 24
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE29:
	.size	main, .-main
	.globl	block
	.bss
	.align 32
	.type	block, @object
	.size	block, 512
block:
	.zero	512
	.comm	prefix_sum,40000020,32
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
