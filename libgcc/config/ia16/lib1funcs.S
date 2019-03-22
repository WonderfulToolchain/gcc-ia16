	.arch i8086,jumps
	.code16
	.att_syntax prefix

	.text

#if defined L_udivsi3 || defined L_umodsi3
# ifdef L_udivsi3
	.global	__udivsi3
	.type	__udivsi3, @function
__udivsi3:
# else
	.global	__umodsi3
	.type	__umodsi3, @function
__umodsi3:
# endif
# if defined __IA16_CALLCVT_CDECL
	movw	%sp,	%bx
	movw	2(%bx),	%ax
	movw	4(%bx),	%dx
	movw	8(%bx),	%cx
	movw	6(%bx),	%bx
# elif defined __IA16_CALLCVT_STDCALL
	/* Pop arguments but "push" the return address back.  */
	popw	%cx
	movw	%sp,	%bx
	xchgw	%cx,	6(%bx)
	popw	%ax
	popw	%dx
	popw	%bx
# elif defined __IA16_CALLCVT_REGPARMCALL
	popw	%cx
	movw	%sp,	%bx
	xchgw	%cx,	2(%bx)
	popw	%bx
# else
#   error "unknown calling convention!"
# endif
	/* Then invoke our helper routine.  */
# ifdef L_udivsi3
	jmp	__ia16_ldivmodu
# else
	call	__ia16_ldivmodu
	movw	%cx,	%dx
	movw	%bx,	%ax
	ret
# endif
#elif defined L_ia16_ldivmodu
	/*
	 * 32-bit division routine (https://github.com/FDOS/kernel/blob/
	 * e6d427834fb5f414ecb984b87454d5df39f2f571/kernel/ludivmul.inc)
	 * adapted by Bart Oldeman from code by Norbert Juffa, translated
	 * into AT&T assembly syntax.  -- tkchia
	 *
	 *	"divide dx:ax / cx:bx, quotient in dx:ax, remainder in cx:bx"
	 */
	.global	__ia16_ldivmodu
	.type	__ia16_ldivmodu, @function
__ia16_ldivmodu:
	testw	%cx,	%cx
	jnz	.big_divisor
	cmpw	%bx,	%dx
	jb	.one_div
	xchgw	%ax,	%cx
	xchgw	%ax,	%dx
	divw	%bx
	xchgw	%ax,	%cx
.one_div:
	divw	%bx
	movw	%dx,	%bx
	movw	%cx,	%dx
	xorw	%cx,	%cx
	ret
.big_divisor:
	pushw	%si
	pushw	%di
	pushw	%dx
	pushw	%ax
	movw	%bx,	%si
	movw	%cx,	%di
.shift_loop:
	shrw	%dx
	rcrw	%ax
	shrw	%cx
	rcrw	%bx
	jnz	.shift_loop
	divw	%bx
	popw	%bx
	movw	%ax,	%cx
	mulw	%di
	popw	%dx
	subw	%ax,	%dx
	pushw	%dx
	movw	%cx,	%ax
	mulw	%si
	subw	%ax,	%bx
	movw	%cx,	%ax
	popw	%cx
	sbbw	%dx,	%cx
	sbbw	%dx,	%dx
	andw	%dx,	%si
	andw	%dx,	%di
	addw	%si,	%bx
	adcw	%di,	%cx
	addw	%dx,	%ax
	xorw	%dx,	%dx
	popw	%di
	popw	%si
	ret
#elif defined L_ne_sf
	/* Cheat a bit here: define __nesf2, __ltsf2, and __lesf2 in the
	   same module, since we can collapse all of them to the same jump
	   anyway.  The modules for __ltsf2 and __lesf2 do not need to
	   define anything then.  Ditto for __*df2.

	   It would be better if ELF supports aliases to external symbols
	   (blog.omega-prime.co.uk/2011/07/06/the-sad-state-of-symbol-aliases/)
	   --- then we can get rid of even the jump.  -- tkchia 20190322 */
	.global	__nesf2
	.global	__ltsf2
	.global	__lesf2
__nesf2:
__ltsf2:
__lesf2:
	jmp	__eqsf2
#elif defined L_gt_sf
	.global	__gtsf2
__gtsf2:
	jmp	__gesf2
#elif defined L_ne_df
	.global	__nedf2
	.global	__ltdf2
	.global	__ledf2
__nedf2:
__ltdf2:
__ledf2:
	jmp	__eqdf2
#elif defined L_gt_df
	.global	__gtdf2
__gtdf2:
	jmp	__gedf2
#endif
