	.file	"secret.c"
	.text
	.p2align 4,,15
	.type	output._omp_fn.0, @function
output._omp_fn.0:
.LFB34:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movl	20(%rdi), %ebx
	call	omp_get_num_threads
	movl	%eax, %r12d
	call	omp_get_thread_num
	movl	%eax, %esi
	movl	%ebx, %eax
	cltd
	idivl	%r12d
	cmpl	%edx, %esi
	jge	.L8
	addl	$1, %eax
	xorl	%edx, %edx
.L8:
	imull	%eax, %esi
	addl	%edx, %esi
	leal	(%rsi,%rax), %r10d
	cmpl	%r10d, %esi
	jge	.L1
	movq	8(%rbp), %r11
.L5:
	movl	16(%rbp), %edi
	movl	%esi, %ecx
	leal	1(%rsi), %r9d
	imull	%edi, %ecx
	movl	%ecx, %eax
	cltd
	idivl	%ebx
	leal	1(%rax), %r12d
	movl	%eax, %r8d
	leal	(%rcx,%rdi), %eax
	cltd
	idivl	%ebx
	cmpl	%eax, %r12d
	jg	.L11
	movq	0(%rbp), %rdx
	subl	%r8d, %eax
	movslq	%r12d, %r12
	subl	$1, %eax
	leaq	(%rdx,%r12,4), %rcx
	addq	%rax, %r12
	xorl	%eax, %eax
	leaq	4(%rdx,%r12,4), %rdx
	.p2align 4,,10
	.p2align 3
.L7:
	imull	$10007, %eax, %eax
	addq	$4, %rcx
	addl	-4(%rcx), %eax
	cmpq	%rdx, %rcx
	jne	.L7
.L6:
	movslq	%esi, %rsi
	cmpl	%r10d, %r9d
	movl	%eax, (%r11,%rsi,4)
	je	.L1
	movl	20(%rbp), %ebx
	movl	%r9d, %esi
	jmp	.L5
	.p2align 4,,10
	.p2align 3
.L1:
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
.L11:
	.cfi_restore_state
	xorl	%eax, %eax
	jmp	.L6
	.cfi_endproc
.LFE34:
	.size	output._omp_fn.0, .-output._omp_fn.0
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%u\n"
	.text
	.p2align 4,,15
	.globl	output
	.type	output, @function
output:
.LFB33:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movl	%esi, %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rdi, %rbx
	movl	$4, %edi
	subq	$56, %rsp
	.cfi_def_cfa_offset 80
	call	omp_set_num_threads
	leaq	16(%rsp), %rsi
	xorl	%edx, %edx
	movl	$output._omp_fn.0, %edi
	movl	%ebp, 32(%rsp)
	movq	$0, (%rsp)
	movq	$0, 8(%rsp)
	movq	%rbx, 16(%rsp)
	movq	%rsp, 24(%rsp)
	movl	$4, 36(%rsp)
	call	GOMP_parallel_start
	leaq	16(%rsp), %rdi
	call	output._omp_fn.0
	call	GOMP_parallel_end
	movl	36(%rsp), %r9d
	movl	32(%rsp), %ebp
	testl	%r9d, %r9d
	jle	.L18
	xorl	%esi, %esi
	xorl	%r11d, %r11d
	xorl	%r10d, %r10d
.L17:
	leal	0(%rbp,%rsi), %ebx
	movl	%ebx, %eax
	cltd
	idivl	%r9d
	movl	%eax, %ecx
	movl	%esi, %eax
	cltd
	idivl	%r9d
	subl	%eax, %ecx
	je	.L19
	movl	$10007, %esi
	movl	$1, %edi
	.p2align 4,,10
	.p2align 3
.L16:
	movl	%edi, %r8d
	imull	%esi, %r8d
	testb	$1, %cl
	cmovne	%r8d, %edi
	imull	%esi, %esi
	shrl	%ecx
	jne	.L16
.L14:
	imull	%edi, %r10d
	addl	(%rsp,%r11,4), %r10d
	addq	$1, %r11
	cmpl	%r11d, %r9d
	jle	.L13
	movl	%ebx, %esi
	jmp	.L17
.L18:
	xorl	%r10d, %r10d
.L13:
	movl	%r10d, %edx
	movl	$.LC0, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L19:
	.cfi_restore_state
	movl	$1, %edi
	jmp	.L14
	.cfi_endproc
.LFE33:
	.size	output, .-output
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
