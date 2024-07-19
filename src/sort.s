	.file	"sort.c"
	.text
	.p2align 4
	.globl	insertion_sort
	.type	insertion_sort, @function
insertion_sort:
.LFB0:
	.cfi_startproc
	endbr64
	leal	-1(%rsi), %r9d
	xorl	%r8d, %r8d
	movzbl	%r9b, %r9d
	cmpb	$1, %sil
	jbe	.L1
	.p2align 4,,10
	.p2align 3
.L6:
	movq	8(%rdi,%r8,8), %rcx
	movq	%r8, %rax
	testb	%r8b, %r8b
	jns	.L3
	jmp	.L14
	.p2align 4,,10
	.p2align 3
.L5:
	movq	%rdx, 8(%rdi,%rax,8)
	subq	$1, %rax
	cmpb	$-1, %al
	je	.L9
.L3:
	movq	(%rdi,%rax,8), %rdx
	cmpq	%rcx, %rdx
	jg	.L5
	addq	$1, %r8
	movq	%rcx, 8(%rdi,%rax,8)
	cmpq	%r8, %r9
	jne	.L6
.L1:
	ret
	.p2align 4,,10
	.p2align 3
.L9:
	movq	$-1, %rax
	addq	$1, %r8
	movq	%rcx, 8(%rdi,%rax,8)
	cmpq	%r8, %r9
	jne	.L6
	ret
.L14:
	movsbq	%r8b, %rax
	addq	$1, %r8
	movq	%rcx, 8(%rdi,%rax,8)
	cmpq	%r8, %r9
	jne	.L6
	ret
	.cfi_endproc
.LFE0:
	.size	insertion_sort, .-insertion_sort
	.ident	"GCC: (Ubuntu 13.2.0-23ubuntu4) 13.2.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
