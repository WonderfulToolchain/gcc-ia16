/* main () function for __attribute__ ((no_assume_ds_data, no_assume_ss_data))
   test cases.  */

	.arch	i8086, jumps
	.code16

	.set	EVIL_STACK_SIZE, 0x400	/* size of away-from-%ds stack */

	.data

	.bss

	.balign	2
	.skip	16			/* pad to make sure stack area does
					   not begin data segment */
evil_stack_start:
	.skip	EVIL_STACK_SIZE
evil_stack_end:

	.text

	.global	main
main:
	movw	$evil_stack_start, %ax
	movw	%ax,	%dx
	mov	$4,	%cl
	shrw	%cl,	%dx
	jz	.fail
	movw	%ds,	%cx
	addw	%cx,	%dx
	andw	$0x000f, %ax
	addw	$evil_stack_end-evil_stack_start, %ax
	movw	%sp,	%bx
	movw	%ss,	%cx
	cli
	movw	%dx,	%ss
	movw	%ax,	%sp
	sti
	pushw	%cx			/* remember old %ss:%sp */
	pushw	%bx
	movw	$0x6bd4, %ax
	movw	%ax,	%ds
	call	do_stuff
	testw	%ax,	%ax
	jnz	.fail
	popw	%bx
	cli
	popw	%ss
	movw	%bx,	%sp
	sti
	movw	%ds,	%ax
	cmpw	$0x6bd4, %ax
	jnz	.fail
	jmp	check_stuff
.fail:
	call	abort
