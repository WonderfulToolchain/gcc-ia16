/* IA-16 far -> near call thunks without argument popping, and with a known
   small immediate number of stack argument bytes

   Copyright (C) 2020 Free Software Foundation, Inc.
   Written By TK Chia

This file is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3, or (at your option) any
later version.

This file is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.

You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */

#include "ia16-preamble.h"

#ifndef ARGS_SZ
# error
#endif
#if ARGS_SZ < 0 || ARGS_SZ % 2 != 0 || ARGS_SZ > 8
# error
#endif

#define PA(x, y)	PA_(x,y)
#define PA_(x, y)	x##y

	/* These routines must go into the near text segment, if at all.  */
	.text

	.global	PA(__ia16_far_call_thunk.bx.,ARGS_SZ)
	.type	PA(__ia16_far_call_thunk.bx.,ARGS_SZ), @function
PA(__ia16_far_call_thunk.bx.,ARGS_SZ):
#if ARGS_SZ				/* set up stack frame */
	pushw	%bp
	movw	%sp,	%bp
#endif
#if ARGS_SZ >= 8			/* re-push stack arguments */
	pushw	12(%bp)
#endif
#if ARGS_SZ >= 6
	pushw	10(%bp)
#endif
#if ARGS_SZ >= 4
	pushw	8(%bp)
#endif
#if ARGS_SZ
	pushw	6(%bp)
#endif
	callw	*%bx
#if ARGS_SZ				/* tear down stack frame and return */
	movw	%bp,	%sp
	popw	%bp
#endif
	lretw
