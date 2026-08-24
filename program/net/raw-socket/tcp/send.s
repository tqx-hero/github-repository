	.file	"send_syn.c"
	.text
	.section	.rodata
.LC0:
	.string	"create socket error"
.LC1:
	.string	"ens33"
.LC2:
	.string	"get hw addr error"
.LC3:
	.string	"get addr error"
.LC4:
	.string	"get hw index error"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$2680, %rsp
	.cfi_offset 3, -24
	movl	%edi, -2660(%rbp)
	movq	%rsi, -2672(%rbp)
	movq	%rdx, -2680(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movl	$3, %edi
	call	htons@PLT
	movzwl	%ax, %eax
	movl	%eax, %edx
	movl	$3, %esi
	movl	$17, %edi
	call	socket@PLT
	movl	%eax, -2644(%rbp)
	cmpl	$-1, -2644(%rbp)
	jne	.L2
	leaq	.LC0(%rip), %rdi
	call	perror_exit
.L2:
	movabsq	$235201253028492, %rax
	movabsq	$19421807752773632, %rdx
	movq	%rax, -1536(%rbp)
	movq	%rdx, -1528(%rbp)
	movabsq	$450359962753826816, %rax
	movabsq	$-6287025079809212416, %rdx
	movq	%rax, -1520(%rbp)
	movq	%rdx, -1512(%rbp)
	movl	$1793, %eax
	movabsq	$22517998136852736, %rdx
	movq	%rax, -1504(%rbp)
	movq	%rdx, -1496(%rbp)
	movq	$0, -1488(%rbp)
	movq	$0, -1480(%rbp)
	leaq	-1472(%rbp), %rdx
	movl	$0, %eax
	movl	$179, %ecx
	movq	%rdx, %rdi
	rep stosq
	movq	%rdi, %rdx
	movl	%eax, (%rdx)
	addq	$4, %rdx
	leaq	-2608(%rbp), %rax
	movl	$16, %edx
	leaq	.LC1(%rip), %rsi
	movq	%rax, %rdi
	call	memcpy@PLT
	leaq	-2608(%rbp), %rdx
	movl	-2644(%rbp), %eax
	movl	$35111, %esi
	movl	%eax, %edi
	movl	$0, %eax
	call	ioctl@PLT
	cmpl	$-1, %eax
	jne	.L3
	movl	-2644(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC2(%rip), %rdi
	call	perror_close_exit
.L3:
	leaq	-1536(%rbp), %rax
	addq	$6, %rax
	leaq	-2608(%rbp), %rdx
	leaq	18(%rdx), %rcx
	movl	$6, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy@PLT
	leaq	-2608(%rbp), %rdx
	movl	-2644(%rbp), %eax
	movl	$35093, %esi
	movl	%eax, %edi
	movl	$0, %eax
	call	ioctl@PLT
	cmpl	$-1, %eax
	jne	.L4
	movl	-2644(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC3(%rip), %rdi
	call	perror_close_exit
.L4:
	leaq	-2608(%rbp), %rax
	addq	$16, %rax
	leaq	4(%rax), %rdx
	leaq	-1536(%rbp), %rax
	addq	$26, %rax
	movl	(%rdx), %edx
	movl	%edx, (%rax)
	leaq	-1536(%rbp), %rbx
	addq	$16, %rbx
	movl	$40, %edi
	call	htons@PLT
	movw	%ax, (%rbx)
	leaq	-1536(%rbp), %rax
	addq	$14, %rax
	movl	$20, %esi
	movq	%rax, %rdi
	call	check_sum
	movzwl	%ax, %eax
	leaq	-1536(%rbp), %rbx
	addq	$24, %rbx
	movl	%eax, %edi
	call	htons@PLT
	movw	%ax, (%rbx)
	leaq	-1536(%rbp), %rbx
	addq	$34, %rbx
	movl	$12000, %edi
	call	htons@PLT
	movw	%ax, (%rbx)
	leaq	-1536(%rbp), %rbx
	addq	$36, %rbx
	movl	$12000, %edi
	call	htons@PLT
	movw	%ax, (%rbx)
	movb	$2, -1489(%rbp)
	leaq	-1536(%rbp), %rbx
	addq	$48, %rbx
	movl	$60000, %edi
	call	htons@PLT
	movw	%ax, (%rbx)
	movabsq	$504870178815846592, %rax
	movl	$335545856, %edx
	movq	%rax, -2560(%rbp)
	movq	%rdx, -2552(%rbp)
	leaq	-2544(%rbp), %rdx
	movl	$0, %eax
	movl	$126, %ecx
	movq	%rdx, %rdi
	rep stosq
	leaq	-1536(%rbp), %rcx
	addq	$34, %rcx
	leaq	-2560(%rbp), %rax
	addq	$12, %rax
	movl	$20, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy@PLT
	leaq	-2560(%rbp), %rax
	movl	$32, %esi
	movq	%rax, %rdi
	call	check_sum
	movzwl	%ax, %eax
	leaq	-1536(%rbp), %rbx
	addq	$50, %rbx
	movl	%eax, %edi
	call	htons@PLT
	movw	%ax, (%rbx)
	leaq	-2640(%rbp), %rax
	movq	$0, (%rax)
	movq	$0, 8(%rax)
	movl	$0, 16(%rax)
	leaq	-2608(%rbp), %rdx
	movl	-2644(%rbp), %eax
	movl	$35123, %esi
	movl	%eax, %edi
	movl	$0, %eax
	call	ioctl@PLT
	cmpl	$-1, %eax
	jne	.L5
	movl	-2644(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC4(%rip), %rdi
	call	perror_close_exit
.L5:
	movl	-2592(%rbp), %eax
	movl	%eax, -2636(%rbp)
	leaq	-1536(%rbp), %rax
	addq	$54, %rax
	movl	$0, (%rax)
	movw	$0, 4(%rax)
	leaq	-2640(%rbp), %rdx
	leaq	-1536(%rbp), %rsi
	movl	-2644(%rbp), %eax
	movl	$20, %r9d
	movq	%rdx, %r8
	movl	$0, %ecx
	movl	$60, %edx
	movl	%eax, %edi
	call	sendto@PLT
	movl	$0, %eax
	movq	-24(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L7
	call	__stack_chk_fail@PLT
.L7:
	addq	$2680, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.globl	check_sum
	.type	check_sum, @function
check_sum:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L9
.L10:
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	sall	$8, %eax
	movl	%eax, %edx
	movq	-24(%rbp), %rax
	addq	$1, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	orl	%edx, %eax
	addl	%eax, -4(%rbp)
	addq	$2, -24(%rbp)
	subl	$2, -28(%rbp)
.L9:
	cmpl	$1, -28(%rbp)
	jg	.L10
	cmpl	$0, -28(%rbp)
	je	.L12
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	sall	$8, %eax
	addl	%eax, -4(%rbp)
	jmp	.L12
.L13:
	movl	-4(%rbp), %eax
	movzwl	%ax, %eax
	movl	-4(%rbp), %edx
	shrl	$16, %edx
	addl	%edx, %eax
	movl	%eax, -4(%rbp)
.L12:
	movl	-4(%rbp), %eax
	shrl	$16, %eax
	testl	%eax, %eax
	jne	.L13
	movl	-4(%rbp), %eax
	notl	%eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	check_sum, .-check_sum
	.globl	perror_exit
	.type	perror_exit, @function
perror_exit:
.LFB8:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	perror@PLT
	movl	$-1, %edi
	call	exit@PLT
	.cfi_endproc
.LFE8:
	.size	perror_exit, .-perror_exit
	.globl	perror_close_exit
	.type	perror_close_exit, @function
perror_close_exit:
.LFB9:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	-12(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	perror_exit
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	perror_close_exit, .-perror_close_exit
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.2) 9.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
